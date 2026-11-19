#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
#include "../../cpp/p0217_contains_duplicate.cpp"

void exact(std::vector<int> values, bool expected) {
    const auto before = values;
    assert(Solution().containsDuplicate(values) == expected);
    assert(values == before);
    std::reverse(values.begin(), values.end());
    const auto reversedBefore = values;
    assert(Solution().containsDuplicate(values) == expected);
    assert(values == reversedBefore);
}

void enumerate(std::vector<int>& values, int remaining, int& count) {
    if (!remaining) {
        bool expected = false;
        for (std::size_t first = 0; first < values.size(); ++first)
            for (std::size_t second = first + 1; second < values.size(); ++second)
                if (values[first] == values[second]) expected = true;
        exact(values, expected);
        ++count;
        return;
    }
    for (int value : {-1, 0, 1}) {
        values.push_back(value);
        enumerate(values, remaining - 1, count);
        values.pop_back();
    }
}

int main() {
    exact({1, 2, 3, 1}, true);
    exact({INT_MIN, INT_MAX, 0}, false);
    exact({INT_MIN, INT_MAX, INT_MIN}, true);
    int checked = 0;
    std::vector<int> values;
    for (int length = 0; length <= 7; ++length) enumerate(values, length, checked);
    assert(checked == 3280);
    std::vector<int> boundary(100000);
    for (int i = 0; i < 100000; ++i) boundary[i] = i;
    exact(boundary, false);
    boundary.back() = 0;
    exact(boundary, true);
    std::cout << "3280 arrays matched pairwise oracle; 3 fixtures and 2 length boundaries passed; reversal invariance checked; input unchanged\n";
}
