#include <cstdint>
#include <unordered_map>
#include <list>

template<typename Value, typename Key = int>
class LRUCache {    
    using ListIt = typename std::list<Value>::iterator;

    std::unordered_map<Key, ListIt> lookupTable;
    std::list<Value> values;
    std::size_t capacity_;
public:
    LRUCache(std::size_t capacity);
    Value get(Key key);
    void put(Key key, Value value);
};