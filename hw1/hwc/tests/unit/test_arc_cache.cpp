#include <gtest/gtest.h>
#include "arc_cache.hpp"
#include "get_pages.hpp"
#include <functional>
#include <vector>

using namespace caches;
using namespace page_getters;

TEST(ArcCacheTest, BasicLookupAndUpdate) {
    ArcCache<int> cache(2);
    
    EXPECT_FALSE(cache.lookup_update(1, slow_get_page_int));
    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
}

TEST(ArcCacheTest, CapacityLimit) {
    ArcCache<int> cache(3);
    
    cache.lookup_update(1, slow_get_page_int);
    cache.lookup_update(2, slow_get_page_int);
    cache.lookup_update(3, slow_get_page_int);
    
    EXPECT_EQ(cache.size(), 3);
    
    cache.lookup_update(4, slow_get_page_int);
    
    EXPECT_EQ(cache.size(), 3);
}

TEST(ArcCacheTest, LRUBehavior) {
    ArcCache<int> cache(3);
    
    cache.lookup_update(1, slow_get_page_int);
    cache.lookup_update(2, slow_get_page_int);
    cache.lookup_update(3, slow_get_page_int);
    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
 
    cache.lookup_update(4, slow_get_page_int);
    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
    EXPECT_FALSE(cache.lookup_update(2, slow_get_page_int));

    cache.lookup_update(5, slow_get_page_int);
    EXPECT_FALSE(cache.lookup_update(3, slow_get_page_int));
}

TEST(ArcCacheTest, MoveFromT1ToT2) {
    ArcCache<int> cache(3);

    cache.lookup_update(1, slow_get_page_int);

    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
 
    cache.lookup_update(2, slow_get_page_int);
    cache.lookup_update(3, slow_get_page_int);
    cache.lookup_update(4, slow_get_page_int);
    cache.lookup_update(5, slow_get_page_int);
    
    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
}

TEST(ArcCacheTest, GhostListFunctionality) {
    ArcCache<int> cache(2);
    
    cache.lookup_update(1, slow_get_page_int);
    cache.lookup_update(2, slow_get_page_int);
    cache.lookup_update(3, slow_get_page_int);
    
    EXPECT_FALSE(cache.lookup_update(1, slow_get_page_int));
    
    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
}

TEST(ArcCacheTest, PulsatingLoad) {
    ArcCache<int> cache(4);
    
    for (int i = 0; i < 2; i++) {
        cache.lookup_update(1, slow_get_page_int);
        cache.lookup_update(2, slow_get_page_int);
        cache.lookup_update(3, slow_get_page_int);
    }
    
    for (int i = 1000; i < 2000; i++) {
        cache.lookup_update(i, slow_get_page_int);
    }

    EXPECT_TRUE(cache.lookup_update(1, slow_get_page_int));
    EXPECT_TRUE(cache.lookup_update(2, slow_get_page_int));
    EXPECT_TRUE(cache.lookup_update(3, slow_get_page_int));
}

TEST(ArcCacheTest, ClearFunction) {
    ArcCache<int> cache(3);
    
    cache.lookup_update(1, slow_get_page_int);
    cache.lookup_update(2, slow_get_page_int);
    cache.lookup_update(3, slow_get_page_int);
    
    EXPECT_EQ(cache.size(), 3);
    
    cache.clear();
    
    EXPECT_EQ(cache.size(), 0);
    
    EXPECT_FALSE(cache.lookup_update(1, slow_get_page_int));
}

