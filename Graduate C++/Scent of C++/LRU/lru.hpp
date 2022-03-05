#include <cstdint>

template<typename Value, typename Key = int>
class LRUCache {
public:
    LRUCache(std::size_t capacity);
    Value get(Key key);
    void put(Key key, Value value);
};