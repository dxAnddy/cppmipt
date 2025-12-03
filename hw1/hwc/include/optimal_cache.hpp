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
    std::unordered_map<KeyT, std::vector<size_t>> request_positions_;

    void build_accesses_positions();
    size_t find_next_use_position(KeyT key);
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
void OptimalCache<T, KeyT>::build_accesses_positions() {
    future_accesses_.clear();
    for(size_t i = 0 ; i < future_accesses_.size(); i++) {
        request_positions_[future_accesses_[i]].push_back(i);
    }

    for(auto &entry : request_positions_) {
        entry.second.push_back(std::numeric_limits<size_t>::max());
    }
}

template <typename T, typename KeyT>
size_t OptimalCache<T, KeyT>::find_next_use_position(KeyT key) {

}

template <typename T, typename KeyT>
OptimalCache<T, KeyT>::ListIt OptimalCache<T, KeyT>::find_entry_to_evict() {
    return std::max(cache_.begin(), cache_.end());
}

template <typename T, typename KeyT>
bool OptimalCache<T, KeyT>::lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) {

}

template <typename T, typename KeyT>
OptimalCache<T, KeyT>::OptimalCache(size_t capacity, std::vector<KeyT> future_accesses) 
: ICache<T, KeyT>(capacity), future_accesses_(future_accesses) {
    if(future_accesses_.empty())
        throw std::invalid_argument("Future accesses sequence can not be empty for Optimal Cache");
    build_accesses_positions();
}

template <typename T, typename KeyT>
struct OptimalCache<T, KeyT>::CacheEntry {
    KeyT key;
    T value;
    size_t next_use;

    bool operator < (const CacheEntry &other) {
        return next_use < other.next_use;
    }
};

}