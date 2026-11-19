#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "../../cpp/p0088_merge_sorted_array.cpp"

void check(const std::vector<int>& first, const std::vector<int>& second, int placeholder = 0) {
    auto expected = first;
    expected.insert(expected.end(), second.begin(), second.end());
    std::sort(expected.begin(), expected.end());
    auto destination = first;
    destination.resize(first.size() + second.size(), placeholder);
    auto source = second;
    const int* const data = destination.data();
    Solution().merge(destination, static_cast<int>(first.size()), source, static_cast<int>(second.size()));
    assert(destination == expected);
    assert(destination.data() == data);
    assert(source == second);
}

void enumerate(std::vector<int>& values, int minimum, int remaining, std::vector<std::vector<int>>& cases) {
    if (!remaining) { cases.push_back(values); return; }
    for (int value = minimum; value <= 1; ++value) {
        values.push_back(value);
        enumerate(values, value, remaining - 1, cases);
        values.pop_back();
    }
}

int main() {
    check({2, 3}, {1}); // A forward write would destroy the unread 2.
    std::vector<std::vector<int>> cases;
    std::vector<int> values;
    for (int length = 0; length <= 4; ++length) enumerate(values, -1, length, cases);
    assert(cases.size() == 35);
    for (const auto& first : cases) {
        for (const auto& second : cases) {
            check(first, second);
            check(first, second, -1000000000);
            check(first, second, 1000000000);
        }
    }
    check(std::vector<int>(200, 1), {});
    check({}, std::vector<int>(200, -1));
    check(std::vector<int>(100, 7), std::vector<int>(100, 7));
    check({-1000000000, 1000000000}, {-1000000000, 0, 1000000000});
    std::cout << "1225 sorted pairs matched sort oracle; 5 fixtures, 2450 alternate-padding checks and storage/source preservation passed\n";
}
