#include <gtest/gtest.h>
#include "lru_cache.hpp"

TEST(LRUCacheTest, BasicOperations) {
    caches::LRUCache<int> cache(2);
    

    EXPECT_FALSE(cache.lookup_update(1, 100));
    EXPECT_EQ(cache.size(), 1);
    

    EXPECT_TRUE(cache.lookup_update(1, 200));
    EXPECT_EQ(cache.size(), 1);
    

    EXPECT_FALSE(cache.lookup_update(2, 300));
    EXPECT_EQ(cache.size(), 2);

    EXPECT_FALSE(cache.lookup_update(3, 400));
    EXPECT_EQ(cache.size(), 2);
}

TEST(LRUCacheTest, Capacity) {
    caches::LRUCache<std::string, int> cache(3);
    
    EXPECT_EQ(cache.capacity(), 3);
    EXPECT_EQ(cache.size(), 0);
    
    cache.lookup_update(1, "one");
    cache.lookup_update(2, "two");
    cache.lookup_update(3, "three");
    
    EXPECT_EQ(cache.size(), 3);
    

    cache.lookup_update(4, "four");
    EXPECT_EQ(cache.size(), 3);
}

TEST(LRUCacheTest, LRUPolicy) {
    caches::LRUCache<int> cache(3);

    EXPECT_FALSE(cache.lookup_update(1, 100));
    EXPECT_FALSE(cache.lookup_update(2, 200));
    EXPECT_FALSE(cache.lookup_update(3, 300));
    EXPECT_TRUE(cache.lookup_update(1, 150));

    EXPECT_FALSE(cache.lookup_update(4, 400));

}

TEST(LRUCacheTest, Clear) {
    caches::LRUCache<int> cache(5);
    
    cache.lookup_update(1, 100);
    cache.lookup_update(2, 200);
    EXPECT_EQ(cache.size(), 2);
    
    cache.clear();
    EXPECT_EQ(cache.size(), 0);
}

TEST(LRUCacheTest, InvalidCapacity) {
    EXPECT_THROW(caches::LRUCache<int> cache(0), std::invalid_argument);
}
