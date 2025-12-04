#pragma once

#include "cache_interface.hpp"

#include <unordered_map>
#include <list>

namespace caches {
template <typename T, typename KeyT = int>
class ArcCache : public ICache<T, KeyT> {
private:

    size_t p = 0;

    std::list<std::pair<KeyT, T>> T1;
    std::list<KeyT> B1;
    std::list<std::pair<KeyT, T>> T2;
    std::list<KeyT> B2;

    std::unordered_map<KeyT, typename std::list<std::pair<KeyT, T>>> T1_map;
    std::unordered_map<KeyT, typename std::list<KeyT>::iterator> B1_map; 
    std::unordered_map<KeyT, typename std::list<std::pair<KeyT, T>>> T2_map;
    std::unordered_map<KeyT, typename std::list<KeyT>::iterator> B2_map;

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
bool ArcCache<T, KeyT>::lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) {

}

template <typename T, typename KeyT>
void ArcCache<T, KeyT>::clear() {
    T1.clear(); B1.clear();
    T2.clear(); B2.clear();
    T1_map.clear(); B1_map.clear();
    T2_map.clear(); B2_map.clear();
}

}