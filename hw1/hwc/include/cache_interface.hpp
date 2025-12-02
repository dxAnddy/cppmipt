#pragma once

#include <cstddef>
#include <stdexcept>

namespace caches {

template <typename T, typename KeyT = int>
class ICache {
public:
    template <typename F>
    virtual bool lookup_update(KeyT key, F slow_get_page) = 0;
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