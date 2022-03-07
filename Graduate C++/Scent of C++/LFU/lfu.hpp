#include <unordered_map>
#include <stdexcept>
#include <cstdint>
#include <utility>
#include <list>
#include <algorithm>

constexpr int MAXIMUM_FREQUENCY = 65536;

template<typename T>
class CacheItem {
    static int currentIndex;
    T value;
    int usageCounter{0}, index{0};
public:
    CacheItem(T&& value): value(value), index(currentIndex++) { }
    void increaseUsageCounter() {
        ++usageCounter;
    }

    void setValue(T&& newValue) {
        increaseUsageCounter();
        value = std::move(newValue);
    }
    const T& getValue() const {
        increaseUsageCounter();
        return value;
    }
    T& getValue() {
        increaseUsageCounter();
        return value;
    }

    friend bool operator<(const CacheItem& lhs, const CacheItem& rhs) {
        return std::tie(lhs.usageCounter, lhs.index) < std::tie(rhs.usageCounter, rhs.index);
    }
};

template<typename T>
int CacheItem<T>::currentIndex = 1;

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
        lookupTable.insert({key, CacheItem(values.begin())});
        return false;
    }
};