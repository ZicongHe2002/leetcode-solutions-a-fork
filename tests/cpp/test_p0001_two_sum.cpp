#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

#include "../../cpp/p0001_two_sum.cpp"

// Catches reused indices, lost duplicate values, wrong complements, and mutation.
void checkPair(std::vector<int> nums, int target, std::vector<int> expected) {
    const auto original = nums;
    Solution solver;
    auto actual = solver.twoSum(nums, target);
    assert(nums == original);
    assert(actual.size() == 2);
    assert(actual[0] != actual[1]);
    for (int index : actual) {
        assert(index >= 0 && index < static_cast<int>(nums.size()));
    }
    assert(static_cast<long long>(nums[actual[0]]) + nums[actual[1]] == target);
    std::sort(actual.begin(), actual.end());
    std::sort(expected.begin(), expected.end());
    assert(actual == expected);
}


// Uses all distinct index pairs rather than a hash table.
void checkAgainstPairOracle(std::vector<int> nums, int target) {
    const auto original = nums;
    std::vector<std::vector<int>> valid;
    for (int left = 0; left < static_cast<int>(nums.size()); ++left) {
        for (int right = left + 1; right < static_cast<int>(nums.size()); ++right) {
            if (static_cast<long long>(nums[left]) + nums[right] == target) {
                valid.push_back({left, right});
            }
        }
    }
    auto actual = Solution{}.twoSum(nums, target);
    assert(nums == original);
    if (valid.empty()) {
        assert(actual.empty());
        return;
    }
    assert(actual.size() == 2);
    std::sort(actual.begin(), actual.end());
    assert(std::find(valid.begin(), valid.end(), actual) != valid.end());
}

int main() {
    checkPair({2, 7, 11, 15}, 9, {0, 1});
    checkPair({3, 2, 4}, 6, {1, 2});
    checkPair({3, 3}, 6, {0, 1});
    checkPair({-3, 4, 3, 90}, 0, {0, 2});
    checkPair({0, 4, 3, 0}, 0, {0, 3});
    checkPair({-1000000000, 1000000000}, 0, {0, 1});
    // Wider than LeetCode's value domain: checks the documented wide arithmetic.
    checkPair({INT_MIN, 0, INT_MAX}, INT_MAX, {1, 2});
    checkPair({INT_MIN, INT_MAX}, -1, {0, 1});
    std::vector<int> noPair{1, 2};
    assert(Solution{}.twoSum(noPair, 100).empty());
    int checked = 0;
    int combinations = 1;
    for (int length = 0; length <= 5; ++length) {
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::vector<int> nums(length);
            for (int& element : nums) {
                element = value % 5 - 2;
                value /= 5;
            }
            for (int target = -4; target <= 4; ++target) {
                checkAgainstPairOracle(nums, target);
                ++checked;
            }
        }
        combinations *= 5;
    }
    assert(checked == 35154);
    std::cout << "Two Sum: 8 valid-pair cases, no-solution extension and 35154 oracle checks passed\n";
}
