#include <gtest/gtest.h>

#include <optimal_cache.hpp>
#include <get_pages.hpp>

TEST(OptimalCacheTest, InvalidVector) {
    EXPECT_THROW(caches::OptimalCache<int> cache(5, std::vector<int>{}), std::invalid_argument);
}

TEST(OptimalCacheTest, ConstructorAndBasicMethods) {
    std::vector<int> future_accesses = {1, 2, 3, 1, 2, 4};
    caches::OptimalCache<int> cache {2, future_accesses};
    EXPECT_EQ(cache.size(), 0);
    EXPECT_EQ(cache.capacity(), 2);
}

TEST(OptimalCacheTest, AccessSequenceMismatch) {
    std::vector<int> future_accesses = {1, 2, 3};
    caches::OptimalCache<int> cache {2, future_accesses};
    EXPECT_NO_THROW(cache.lookup_update(1, page_getters::slow_get_page_int));
    EXPECT_THROW(cache.lookup_update(3, page_getters::slow_get_page_int), std::runtime_error);
}

TEST(OptimalCacheTest, OptimalBehavior) {
    std::vector<int> future_accesses = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    caches::OptimalCache<int> cache(3, future_accesses);

    size_t hits = 0;

    for (size_t i = 0; i < future_accesses.size(); ++i) {
        if (cache.lookup_update(future_accesses[i], page_getters::slow_get_page_int)) {
            ++hits;
        }
    }

    EXPECT_EQ(hits, 5);
}

TEST(OptimalCacheTest, AllUniqueAccesses) {
    std::vector<int> future_accesses;
    for (int i = 0; i < 10; ++i) {
        future_accesses.push_back(i);
    }
    
    caches::OptimalCache<int> cache(3, future_accesses);
    
    size_t hits = 0;
    for (int key : future_accesses) {
        if (cache.lookup_update(key, page_getters::slow_get_page_int)) {
            ++hits;
        }
    }

    EXPECT_EQ(hits, 0u);
}
