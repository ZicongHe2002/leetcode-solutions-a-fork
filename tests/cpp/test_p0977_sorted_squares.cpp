#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "../../cpp/p0977_sorted_squares.cpp"

void check(std::vector<int> values) {
    const auto before = values;
    std::vector<int> expected;
    for (int value : values) expected.push_back(value * value);
    std::sort(expected.begin(), expected.end());
    assert(Solution().sortedSquares(values) == expected);
    assert(values == before);
    auto reflected = values;
    std::reverse(reflected.begin(), reflected.end());
    for (int& value : reflected) value = -value;
    const auto reflectedBefore = reflected;
    assert(Solution().sortedSquares(reflected) == expected);
    assert(reflected == reflectedBefore);
}

void enumerate(std::vector<int>& values, int minimum, int remaining, int& count) {
    if (!remaining) { check(values); ++count; return; }
    for (int value = minimum; value <= 3; ++value) {
        values.push_back(value);
        enumerate(values, value, remaining - 1, count);
        values.pop_back();
    }
}

int main() {
    std::vector<int> sample{-4, -1, 0, 3, 10};
    assert((Solution().sortedSquares(sample) == std::vector<int>{0, 1, 9, 16, 100}));
    int checked = 0;
    std::vector<int> values;
    for (int size = 0; size <= 6; ++size) enumerate(values, -3, size, checked);
    assert(checked == 1716);
    check({-10000, -10000, 0, 10000, 10000});
    check({-10000, -3, -1});
    check(std::vector<int>(10000, 0));
    std::vector<int> boundary(10000);
    for (int i = 0; i < 10000; ++i) boundary[i] = i - 5000;
    check(boundary);
    std::cout << "1716 sorted arrays, one exact fixture and four value/length boundaries passed; reverse-negation checks; input unchanged\n";
}
