#pragma once
#define ENABLE_LRU_CACHE
#ifdef ENABLE_LRU_CACHE
#include "cache_interface.hpp"
#include <list>
#include <unordered_map>

namespace caches {

template <typename T, typename KeyT = int>
class LRUCache : public ICache<T, KeyT> {
private:
    size_t capacity_;
    std::list<std::pair<KeyT, T>> cache_;

    using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

public:
    LRUCache(size_t capacity) : capacity_(capacity) {
        if(capacity == 0)
            throw std::invalid_argument("Cache size must be positive");
    }

    template <typename F>
    bool lookup_update(KeyT key, F slow_get_page) override;

    void clear() override {
        cache_.clear();
        hash_.clear();
    }

    size_t size() const noexcept override {
        return cache_.size();
    }

    size_t capacity() const noexcept override {
        return capacity_;
    }

};

template <typename T, typename KeyT>
template <typename F>
bool LRUCache<T, KeyT>::lookup_update(KeyT key, F slow_get_page) {
    auto hit = hash_.find(key);
    if(hit != hash_.end()) {
        auto eltit = hit->second;
        cache_.splice(cache_.begin(), cache_, eltit);
        return true;
    }
    if(cache_.size() == capacity_) {
        hash_.erase(cache_.back().first);
        cache_.pop_back();
    }

    cache_.emplace_front(key, slow_get_page(key));
    hash_[key] = cache_.begin();
    return false;
}

}
#endif