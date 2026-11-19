#include <algorithm>
#include <list>

class MinStack {
    struct Entry {
        int value;
        int minimum;
    };
    std::list<Entry> entries;

public:
    MinStack() = default;
    void push(int value) {
        const int minimum = entries.empty() ? value : std::min(value, entries.back().minimum);
        entries.push_back({value, minimum});
    }
    void pop() { entries.pop_back(); }
    int top() const { return entries.back().value; }
    int getMin() const { return entries.back().minimum; }
};
