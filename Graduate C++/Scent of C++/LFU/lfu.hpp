#include <cstdint>

template<typename Value, typename Key = int>
class LFUCache {
    std::size_t capacity_;
public:
    LFUCache(std::size_t capacity)
        : capacity_(capacity) {}

    Value get(Key key);
    bool put(Key key, Value value);
};