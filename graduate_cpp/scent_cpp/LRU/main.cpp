#include "lru.hpp"

#include <iostream>

struct DummyType {
    int id;
};

int main() {
    int cache_capacity, count_of_elements;
    std::cin >> cache_capacity >> count_of_elements;
    LRUCache<DummyType> cache(cache_capacity);

    int cache_hit = 0;
    while(count_of_elements--) {
        int key; std::cin >> key;
        if(cache.put(key, DummyType{ key })) {
            cache_hit += 1;
        }
    }
    std::cout << cache_hit << std::endl;
}