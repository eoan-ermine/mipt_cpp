#include <tuple>
#include <utility>

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