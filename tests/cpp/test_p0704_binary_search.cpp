#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "../../cpp/p0704_binary_search.cpp"

void check(std::vector<int> values, int target, int expected) {
    const auto original = values;
    assert(Solution{}.search(values, target) == expected);
    assert(values == original);
}

int main() {
    // Catches closed/half-open endpoint confusion and non-shrinking intervals.
    check({-1, 0, 3, 5, 9, 12}, 9, 4);
    check({-1, 0, 3, 5, 9, 12}, 2, -1);
    check({2, 5}, 2, 0);
    check({2, 5}, 5, 1);
    check({2, 5}, 4, -1);
    check({2, 5}, 6, -1);
    check({5}, 5, 0);
    check({5}, 4, -1);
    check({}, 0, -1);
    const std::vector<int> offsets{-1000, 0, 1000};
    int translationChecks = 0;
    int checked = 0;
    for (int mask = 0; mask < 128; ++mask) {
        std::vector<int> values;
        for (int bit = 0; bit < 7; ++bit) {
            if (mask & (1 << bit)) values.push_back(bit - 3);
        }
        for (int target = -4; target <= 4; ++target) {
            const auto position = std::find(values.begin(), values.end(), target);
            const int expected = position == values.end() ? -1 : static_cast<int>(position - values.begin());
            check(values, target, expected);
            for (int offset : offsets) {
                std::vector<int> shifted;
                shifted.reserve(values.size());
                for (int value : values) shifted.push_back(value + offset);
                check(shifted, target + offset, expected);
                ++translationChecks;
            }
            ++checked;
        }
    }
    assert(checked == 1152);
    assert(translationChecks == 3456);
    std::cout << "Binary search: 9 fixtures and 1152 linear-oracle cases and 3456 translation checks passed\n";
}
