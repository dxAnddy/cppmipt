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


    bool lookup_update(KeyT ket, T value) override;

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
bool lookup_update(KeyT ket, T value) {

    
}

}
#endif