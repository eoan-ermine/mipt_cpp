#include <unordered_map>
#include <stdexcept>
#include <cstdint>
#include <utility>
#include <list>
#include <algorithm>

#include "cache_item.hpp"

template<typename Value, typename Key = int>
class LFUCache {
    using ListIt = typename std::list<Value>::iterator;

    std::unordered_map<Key, CacheItem<ListIt>> lookupTable;
    std::list<Value> values;
    std::size_t capacity_;

    auto get_least_frequently_used() {
        return std::min_element(
            lookupTable.begin(), lookupTable.end(), [](const auto& lhs, const auto& rhs) {
                return lhs.second < rhs.second;
            }
        );
    }
public:
    LFUCache(std::size_t capacity)
        : capacity_(capacity) { }

    Value get(Key key) {
        if(auto it = lookupTable.find(key); it != lookupTable.end()) {
            return *(it->second.getValue());
        }
        throw std::runtime_error{"There are no such key in cache"};
    }

    bool put(Key key, Value value) {
        if(auto it = lookupTable.find(key); it != lookupTable.end()) {
            it->second.increaseUsageCounter();
            return true;
        }
        if(values.size() == capacity_) {
            auto to_delete = get_least_frequently_used();
            values.erase(to_delete->second.getValue());
            lookupTable.erase(to_delete);
        }
        values.push_front(value);
        lookupTable.insert({key, CacheItem<ListIt>(values.begin())});
        return false;
    }
};