#pragma once

#include "cache_interface.hpp"

#include <list>
#include <limits>

namespace caches {

template <typename T, typename KeyT = int>
class OptimalCache : public ICache<T, KeyT> {
private:
    struct CacheEntry;
    std::list<CacheEntry> cache_;
    using ListIt = typename std::list<CacheEntry>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    size_t current_pos_ = 0;
    std::vector<KeyT> future_accesses_;
    std::vector<size_t> next_uses_;

    void precalculate_next_uses();
    typename std::list<CacheEntry>::iterator find_entry_to_evict();

public:
    OptimalCache(size_t capacity, std::vector<KeyT> future_accesses);

    bool lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) override;

    void clear() override {
        cache_.clear();
        hash_.clear();
    }

    size_t size() const noexcept override {
        return cache_.size();
    }

    ~OptimalCache() override = default;
};

template <typename T, typename KeyT>
void OptimalCache<T, KeyT>::precalculate_next_uses() {
    next_uses_.resize(future_accesses_.size());
    std::unordered_map<KeyT, size_t> next_position;

    for(size_t i = 0 ; i < next_uses_.size(); i++)
        next_uses_[i] = std::numeric_limits<size_t>::max();

    for(size_t i = next_uses_.size() - 1; i > 0; --i) {
        KeyT key = future_accesses_[i];
        auto it = next_position.find(key);
        if(it != next_position.end()) {
            next_uses_[i] = it->second;
        }
        next_position[key] = i;
    }
}

template <typename T, typename KeyT>
typename OptimalCache<T, KeyT>::ListIt OptimalCache<T, KeyT>::find_entry_to_evict() {
    return std::max_element(cache_.begin(), cache_.end());
}

template <typename T, typename KeyT>
bool OptimalCache<T, KeyT>::lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) {
    if(current_pos_ >= future_accesses_.size() || future_accesses_[current_pos_] != key)
        throw std::runtime_error("Optimal cache: access sequence doesnt match known future");
    
    auto it = hash_.find(key);
    size_t new_next_use = next_uses_[current_pos_];

    if(it != hash_.end()) {
        it->second->next_use = next_uses_[current_pos_];
        current_pos_++;
        return true;
    }

    current_pos_++;
    if(cache_.size() == this->capacity_) {
        auto evict_it = find_entry_to_evict();
        size_t max_next_use_in_cache = evict_it->next_use;

        if(new_next_use >= max_next_use_in_cache)
            return false;
        
        hash_.erase(evict_it->key);
        cache_.erase(evict_it);
    }

    T value = slow_get_page(key);

    CacheEntry newEntry {
        key,
        value,
        new_next_use
    };

    cache_.push_back(newEntry);
    hash_[key] = std::prev(cache_.end());

    return false;
}

template <typename T, typename KeyT>
OptimalCache<T, KeyT>::OptimalCache(size_t capacity, std::vector<KeyT> future_accesses) 
: ICache<T, KeyT>(capacity), future_accesses_(future_accesses) {
    if(future_accesses_.empty())
        throw std::invalid_argument("Future accesses sequence can not be empty for Optimal Cache");
    precalculate_next_uses();
}

template <typename T, typename KeyT>
struct OptimalCache<T, KeyT>::CacheEntry {
    KeyT key;
    T value;
    size_t next_use;

    bool operator < (const CacheEntry &other) const {
        return next_use < other.next_use;
    }
};

}