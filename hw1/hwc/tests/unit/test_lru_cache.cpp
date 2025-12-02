#include <gtest/gtest.h>

#include "lru_cache.hpp"
#include "get_pages.hpp"

TEST(LRUCacheTest, BasicOperations) {
    using page_getters::slow_get_page_int;
    caches::LRUCache<int> cache(2);

    EXPECT_FALSE(cache.lookup_update(1, slow_get_page_int));
    EXPECT_EQ(cache.size(), 1);
    

    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
    EXPECT_EQ(cache.size(), 1);
    

    EXPECT_FALSE(cache.lookup_update(2, slow_get_page_int));
    EXPECT_EQ(cache.size(), 2);

    EXPECT_FALSE(cache.lookup_update(3, slow_get_page_int));
    EXPECT_EQ(cache.size(), 2);
}

TEST(LRUCacheTest, LRUPolicy) {
    using page_getters::slow_get_page_int;
    caches::LRUCache<int> cache(3);

    EXPECT_FALSE(cache.lookup_update(1, slow_get_page_int));
    EXPECT_FALSE(cache.lookup_update(2, slow_get_page_int));
    EXPECT_FALSE(cache.lookup_update(3, slow_get_page_int));
    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));

    EXPECT_FALSE(cache.lookup_update(4, slow_get_page_int));

}

TEST(LRUCacheTest, Clear) {
    using page_getters::slow_get_page_int;
    caches::LRUCache<int> cache(5);
    
    cache.lookup_update(1, slow_get_page_int);
    cache.lookup_update(2, slow_get_page_int);
    EXPECT_EQ(cache.size(), 2);
    
    cache.clear();
    EXPECT_EQ(cache.size(), 0);
}

TEST(LRUCacheTest, InvalidCapacity) {
    EXPECT_THROW(caches::LRUCache<int> cache(0), std::invalid_argument);
}
