#include "lru.hpp"

#include <stdexcept>

template<typename Value, typename Key>
LRUCache<Value, Key>::LRUCache(std::size_t capacity)
    : capacity_(capacity) {}

template<typename Value, typename Key>
Value LRUCache<Value, Key>::get(Key key) {
    if(auto it = lookupTable.find(key); it != lookupTable.end()) {
        values.splice(lookupTable.begin(), lookupTable, it);
        return *it;
    }
    throw std::runtime_error{"There are no such value in cache"};
}

template<typename Value, typename Key>
void LRUCache<Value, Key>::put(Key key, Value value) {
    if(auto it = lookupTable.find(key); it != lookupTable.end()) {
        values.splice(lookupTable.begin(), lookupTable, it->second);
    } else {
        if(values.size() == capacity_) {
            lookupTable.erase(values.back().id);
            values.pop_back();
        }
        values.push_front(value);
        lookupTable[key] = values.begin();
    }
}