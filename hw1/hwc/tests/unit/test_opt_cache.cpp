#include <gtest/gtest.h>

#include <optimal_cache.hpp>
#include <get_pages.hpp>

TEST(OPT_CACHE_TEST, InvalidVector) {
    EXPECT_THROW(caches::OptimalCache<int> cache(5, std::vector<int>{}), std::invalid_argument);
}

