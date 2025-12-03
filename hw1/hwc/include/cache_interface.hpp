#pragma once

#include <cstddef>
#include <stdexcept>
#include <functional>

namespace caches {

template <typename T, typename KeyT = int>
class ICache {
protected:
    size_t capacity_;
public:
    explicit ICache(size_t capacity);
    virtual bool lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page) = 0;
    virtual void clear() = 0;
    virtual size_t size() const noexcept = 0;
    size_t capacity() const noexcept;
    virtual ~ICache() = default;
};

template <typename T, typename KeyT>
ICache<T, KeyT>::ICache(size_t capacity) : capacity_(capacity) {
    if(capacity == 0)
        throw std::invalid_argument("Cache capacity must  be > 0");
}

template <typename T, typename KeyT>
size_t ICache<T, KeyT>::capacity() const noexcept{
    return capacity_;
}

enum class CacheType {
    LRU,
    ARC,
    OPTIMAL,
};

}