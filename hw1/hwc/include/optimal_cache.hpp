#pragma once

#include "cache_interface.hpp"

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

public:
    OptimalCache(size_t capacity, std::vector<KeyT> future_accesses);
    ~OptimalCache() override = default;
};

template <typename T, typename KeyT>
OptimalCache<T, KeyT>::OptimalCache(size_t capacity, std::vector<KeyT> future_accesses) 
: ICache<T, KeyT>(capacity), future_accesses_(future_accesses) {
    if(future_accesses_.empty())
        throw std::invalid_argument("Future accesses sequence can not be empty for Optimal Cache");
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