#include <cstdint>
#include <unordered_map>
#include <list>

#include <stdexcept>

template<typename Value, typename Key = int>
class LRUCache {    
    using ListIt = typename std::list<Value>::iterator;

    std::unordered_map<Key, ListIt> lookupTable;
    std::list<Value> values;
    std::size_t capacity_;
public:
    LRUCache(std::size_t capacity)
        : capacity_(capacity) {}

    Value get(Key key) {
        if(auto it = lookupTable.find(key); it != lookupTable.end()) {
            values.splice(values.begin(), values, it->second);
            return *(it->second);
        }
        throw std::runtime_error{"There are no such value in cache"};
    }

    bool put(Key key, Value value) {
        if(auto it = lookupTable.find(key); it != lookupTable.end()) {
            values.splice(values.begin(), values, it->second);
            return true;
        }
        if(values.size() == capacity_) {
            lookupTable.erase(values.back().id);
            values.pop_back();
        }
        values.push_front(value);
        lookupTable[key] = values.begin();
        return false;
    }
};