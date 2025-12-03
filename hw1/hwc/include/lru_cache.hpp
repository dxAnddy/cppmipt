#pragma once

#include "cache_interface.hpp"

#include <list>
#include <unordered_map>

namespace caches {

template <typename T, typename KeyT = int>
class LRUCache : public ICache<T, KeyT> {
private:
    std::list<std::pair<KeyT, T>> cache_;

    using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

public:
    LRUCache(size_t capacity) : ICache<T, KeyT>(capacity) {
    }

    bool lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) override;

    void clear() override {
        cache_.clear();
        hash_.clear();
    }

    size_t size() const noexcept override {
        return cache_.size();
    }

};

template <typename T, typename KeyT>
bool LRUCache<T, KeyT>::lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) {
    auto hit = hash_.find(key);
    if(hit != hash_.end()) {
        auto eltit = hit->second;
        cache_.splice(cache_.begin(), cache_, eltit);
        return true;
    }
    if(cache_.size() == this->capacity_) {
        hash_.erase(cache_.back().first);
        cache_.pop_back();
    }

    cache_.emplace_front(key, slow_get_page(key));
    hash_[key] = cache_.begin();
    return false;
}

}