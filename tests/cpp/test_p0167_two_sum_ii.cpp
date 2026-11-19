#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
#include "../../cpp/p0167_two_sum_ii.cpp"

int checkTargets(std::vector<int>& values) {
    const auto before = values;
    int checked = 0;
    for (int target = -4; target <= 4; ++target) {
        std::vector<std::vector<int>> pairs;
        for (int first = 0; first < static_cast<int>(values.size()); ++first)
            for (int second = first + 1; second < static_cast<int>(values.size()); ++second)
                if (values[first] + values[second] == target) pairs.push_back({first + 1, second + 1});
        if (pairs.size() == 1) {
            assert(Solution().twoSum(values, target) == pairs[0]);
            assert(values == before);
            auto shifted = values;
            for (int& value : shifted) value += 3;
            const auto shiftedBefore = shifted;
            assert(Solution().twoSum(shifted, target + 6) == pairs[0]);
            assert(shifted == shiftedBefore);
            ++checked;
        }
    }
    return checked;
}

void enumerate(std::vector<int>& values, int minimum, int remaining, int& count) {
    if (!remaining) { count += checkTargets(values); return; }
    for (int value = minimum; value <= 2; ++value) {
        values.push_back(value);
        enumerate(values, value, remaining - 1, count);
        values.pop_back();
    }
}

void exact(std::vector<int> values, int target, const std::vector<int>& expected) {
    const auto before = values;
    assert(Solution().twoSum(values, target) == expected);
    assert(values == before);
}

void noSolution(std::vector<int> values, int target) {
    const auto before = values;
    bool caught = false;
    try { Solution().twoSum(values, target); }
    catch (const std::invalid_argument&) { caught = true; }
    assert(caught && values == before);
}

int main() {
    exact({2, 7, 11, 15}, 9, {1, 2});
    exact({3, 3}, 6, {1, 2});
    exact({-4, -1, 0, 2, 5, 9}, 4, {2, 5});
    exact({-1000, 1000}, 0, {1, 2});
    exact({INT_MIN, INT_MAX}, -1, {1, 2}); // Value-range extension with a representable sum.
    exact({1, 2, INT_MAX}, 3, {1, 2}); // First probe exceeds INT_MAX; its sign must remain positive.
    exact({INT_MIN, -2, -1}, -3, {2, 3}); // First probe is below INT_MIN; its sign must remain negative.
    int checked = 0;
    std::vector<int> values;
    for (int size = 2; size <= 6; ++size) enumerate(values, -2, size, checked);
    assert(checked > 0);
    noSolution({}, 0);
    noSolution({2}, 4);
    noSolution({1, 2}, 9);
    noSolution({0, 0}, 1);
    std::cout << checked << " unique-pair cases matched all-index-pair oracle; legal translations matched; 7 fixtures and 4 no-solution extensions passed\n";
}
