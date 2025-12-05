#pragma once

#include "cache_interface.hpp"

#include <unordered_map>
#include <list>
#include<cassert>

namespace caches {
template <typename T, typename KeyT = int>
class ArcCache : public ICache<T, KeyT> {
private:

    size_t p = 0;

    std::list<std::pair<KeyT, T>> T1;
    std::list<KeyT> B1;
    std::list<std::pair<KeyT, T>> T2;
    std::list<KeyT> B2;

    std::unordered_map<KeyT, typename std::list<std::pair<KeyT, T>>::iterator> T1_map;
    std::unordered_map<KeyT, typename std::list<KeyT>::iterator> B1_map; 
    std::unordered_map<KeyT, typename std::list<std::pair<KeyT, T>>::iterator> T2_map;
    std::unordered_map<KeyT, typename std::list<KeyT>::iterator> B2_map;

    void replace(KeyT key);
    size_t compute_delta(bool hit_in_b1);
    void adapt_parameter(bool hit_in_b1);

public:
    ArcCache(size_t capacity) : ICache<T, KeyT>(capacity) {
    }

    bool lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) override;

    void clear() override;

    size_t size() const noexcept override {
        return T1.size() + T2.size();
    }

    ~ArcCache() = default;
};

template <typename T, typename KeyT>
void ArcCache<T, KeyT>::replace(KeyT key) {
    auto b2_it = B2_map.find(key);
    bool hit_in_b2 = false;
    if(b2_it != B2_map.end()) 
        hit_in_b2 = true;
    
    if((!T1.empty()) && ((T1.size() > p) || (hit_in_b2 && T1.size() == p) )) {
        auto lru_it = std::prev(T1.end());
        KeyT evicted_key = lru_it->first;

        T1.erase(lru_it);
        T1_map.erase(evicted_key); 

        B1.push_front(evicted_key);
        B1_map[evicted_key] = B1.begin();
    } else {
        auto lru_it = std::prev(T2.end());
        KeyT evicted_key = lru_it->first;
    
        T2.erase(lru_it);
        T2_map.erase(evicted_key);
    
        B2.push_front(evicted_key);
        B2_map[evicted_key] = B2.begin();
    }
}

template <typename T, typename KeyT>
size_t ArcCache<T, KeyT>::compute_delta(bool hit_in_b1) {
    if(hit_in_b1) {
        if(B1.size() >= B2.size())
            return 1;
        return  static_cast<double>(B2.size()) / B1.size();
    } else {
        if(B2.size() >= B1.size())
            return 1;
        return static_cast<double>(B1.size()) / B2.size();
    }
}

template <typename T, typename KeyT>
void ArcCache<T, KeyT>::adapt_parameter(bool hit_in_b1) {
    double delta = compute_delta(hit_in_b1);
    if (hit_in_b1) {
        p = std::min(static_cast<size_t>(p + delta), this->capacity_);
    } else {
        if (delta >= p) {
            p = 0;
        } else {
            p = static_cast<size_t>(p - delta);
        }
    }
}

template <typename T, typename KeyT>
bool ArcCache<T, KeyT>::lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) {
    assert(T1.size() == T1_map.size());
    assert(T2.size() == T2_map.size());
    assert(B1.size() == B1_map.size());
    assert(B2.size() == B2_map.size());
    auto it_T1 = T1_map.find(key);
    if(it_T1 != T1_map.end()) {
        T2.splice(T2.begin(), T1, it_T1->second);
        T2_map[key] = T2.begin();
        T1_map.erase(it_T1);
        return true;
    }

    auto it_T2 = T2_map.find(key);
    if(it_T2 != T2_map.end()) {
        T2.splice(T2.begin(), T2, it_T2->second);
        T2_map[key] = T2.begin();
        return true;
    }

    auto it_B1 = B1_map.find(key);
    if(it_B1 != B1_map.end()) { 
        adapt_parameter(true);
        replace(key);
        B1.erase(it_B1->second);
        B1_map.erase(it_B1);
        T2.push_front({key, slow_get_page(key)});
        T2_map[key] = T2.begin();
        return false;
    }

    auto it_B2 = B2_map.find(key);
    if(it_B2 != B2_map.end()) {
        adapt_parameter(false);
        replace(key);
        B2.erase(it_B2->second);
        B2_map.erase(it_B2);
        T2.push_front({key, slow_get_page(key)});
        T2_map[key] = T2.begin();
        return false;
    }

    if(T1.size() + B1.size() == this->capacity_) {
        
        if(T1.size() < this->capacity_) {
            auto last_key = B1.back();
            B1_map.erase(last_key);
            B1.pop_back();
            replace(key);
        } else {
            auto last_it = std::prev(T1.end());
            T1_map.erase(last_it->first);
            T1.pop_back();
        }
    } else if(T1.size() + B1.size() < this->capacity_) {
        size_t size = T1.size() + T2.size() + B1.size() + B2.size();
        if(size >= this->capacity_) {
            if(size == (this->capacity_) * 2) {
                auto last_key = B2.back();
                B2_map.erase(last_key);
                B2.pop_back();
            }
            replace(key);
        }
    }
    T1.push_front({key, slow_get_page(key)});
    T1_map[key] = T1.begin();

    assert(T1.size() + T2.size() <= this->capacity_);
    assert(T1.size() + B1.size() + B2.size() + T2.size() <= this->capacity_ * 2);
    return false;
}

template <typename T, typename KeyT>
void ArcCache<T, KeyT>::clear() {
    p = 0;
    T1.clear(); B1.clear();
    T2.clear(); B2.clear();
    T1_map.clear(); B1_map.clear();
    T2_map.clear(); B2_map.clear();
}

}