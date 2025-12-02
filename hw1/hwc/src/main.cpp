#include <lru_cache.hpp>
#include <iostream>

//slow get page imitation
int slow_get_page_int(int key) { return key; }

int main() {
    size_t cache_size, num_elems, hits;

    std::cin >> cache_size >> num_elems;

    if(std::cin.bad()) {
        std::cerr << "Invalid input for cache" << std::endl;
        return -1;
    } 

    caches::LRUCache<int> lru_cache {cache_size};

    for(size_t i = 0; i < num_elems; i++) {
        int elem;
        std::cin >> elem;
        if(lru_cache.lookup_update(elem, slow_get_page_int(elem)))
            hits++;
    }

    std::cout << hits << std::endl;
}