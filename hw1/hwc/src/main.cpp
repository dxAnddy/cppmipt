#include <iostream>
#include <vector>

#include "get_pages.hpp"

#if defined(USE_LRU)
    #include "lru_cache.hpp"
#elif defined(USE_OPTIMAL)
    #include "optimal_cache.hpp"
#else
#ifndef __INTELLISENSE__
    #error "No cache type defined. Use -DUSE_LRU, -DUSE_OPTIMAL"
#endif
#endif

int main() {
    size_t cache_size, num_elems, hits = 0;

    std::cin >> cache_size >> num_elems;

    if(std::cin.bad()) {
        std::cerr << "Invalid input for cache" << std::endl;
        return -1;
    }


#ifdef USE_LRU
    caches::LRUCache<int> cache{cache_size};
    for(size_t i = 0; i < num_elems; i++) {
        int elem;
        std::cin >> elem;
        if(cache.lookup_update(elem, page_getters::slow_get_page_int))
            hits++;
    }
#endif

#ifdef USE_OPTIMAL
    std::vector<int> future;
    for(size_t i = 0; i < num_elems; i++) {
        int elem;
        std::cin >> elem;
        future.push_back(elem);
    }
    caches::OptimalCache<int> cache {cache_size, future};

    for(size_t i = 0; i < num_elems; i++) {
        if(cache.lookup_update(future[i], page_getters::slow_get_page_int))
            hits++;
    }
#endif

    std::cout << hits <<std::endl;
}