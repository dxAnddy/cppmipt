#pragma once

#include <cstddef>
#include <stdexcept>
#include <functional>

namespace caches {

template <typename T, typename KeyT = int>
class ICache {
public:
    virtual bool lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) = 0;
    virtual void clear() = 0;
    virtual size_t size() const noexcept = 0;
    virtual size_t capacity() const noexcept = 0;
    virtual ~ICache() = default;
};

enum class CacheType {
#ifdef ENABLE_LRU_CACHE
    LRU,
#endif
#ifdef ENABLE_ARC_CACHE
    ARC,
#endif
#ifdef ENABLE_OPTIMAL_CACHE
    OPTIMAL,
#endif
};

}