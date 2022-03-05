#include <unordered_map>
#include <stdexcept>
#include <cstdint>
#include <utility>
#include <list>

constexpr int MAXIMUM_FREQUENCY = 65536;

template<typename Value, typename Key = int>
class LFUCache {
    using ListIt = typename std::list<Value>::iterator;

    std::unordered_map<Key, std::pair<int, ListIt>> lookupTable;
    std::list<Value> values;
    std::size_t capacity_;

    auto get_least_frequently_used() {
        int minimum_frequency = MAXIMUM_FREQUENCY;
        auto minimum_frequency_iterator = lookupTable.end();

        for(auto it = lookupTable.begin(), end = lookupTable.end(); it != end; ++it) {
            if(auto curFrequency = it->second.first; curFrequency <= minimum_frequency) {
                minimum_frequency = curFrequency;
                minimum_frequency_iterator = it;
            }
        }

        return minimum_frequency_iterator;
    }
public:
    LFUCache(std::size_t capacity)
        : capacity_(capacity) { }

    Value get(Key key) {
        if(auto it = lookupTable.find(key); it != lookupTable.end()) {
            it->second.first += 1;
            return *(it->second->second);
        }
        throw std::runtime_error{"There are no such key in cache"};
    }

    bool put(Key key, Value value) {
        if(auto it = lookupTable.find(key); it != lookupTable.end()) {
            it->second.first += 1;
            return true;
        }
        if(values.size() == capacity_) {
            auto to_delete = get_least_frequently_used();
            values.erase(to_delete->second.second);
            lookupTable.erase(to_delete);
        }
        values.push_front(value);
        lookupTable[key] = {1, values.begin()};
        return false;
    }
};