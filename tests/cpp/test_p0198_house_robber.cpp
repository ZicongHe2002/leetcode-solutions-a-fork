#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "../../cpp/p0198_house_robber.cpp"

int subset_oracle(const std::vector<int>& nums) {
    int best = 0;
    for (unsigned mask = 0; mask < (1u << nums.size()); ++mask) {
        if (mask & (mask << 1)) continue;
        int sum = 0;
        for (unsigned i = 0; i < nums.size(); ++i) if (mask & (1u << i)) sum += nums[i];
        best = std::max(best, sum);
    }
    return best;
}

void check(std::vector<int> nums, int expected) {
    const auto before = nums;
    assert(Solution().rob(nums) == expected);
    assert(nums == before);
}

void enumerate(std::vector<int>& nums, int remaining, int& cases) {
    if (!remaining) {
        const int expected = subset_oracle(nums);
        check(nums, expected);
        if (nums.size() <= 5) {
            for (int factor = 0; factor <= 2; ++factor) {
                auto scaled = nums;
                for (int& value : scaled) value *= factor;
                check(scaled, factor * expected);
            }
            for (std::size_t index = 0; index < nums.size(); ++index) {
                auto increased = nums;
                ++increased[index];
                const int raised = subset_oracle(increased);
                assert(raised >= expected && raised <= expected + 1);
                check(increased, raised);
            }
        }
        ++cases;
        return;
    }
    for (int value = 0; value < 4; ++value) {
        nums.push_back(value);
        enumerate(nums, remaining - 1, cases);
        nums.pop_back();
    }
}

int main() {
    check({2, 7, 9, 3, 1}, 12);
    check({2, 1, 1, 2}, 4);
    check({400}, 400);
    check({0, 0, 0}, 0);
    check({}, 0); // Explicit extension beyond nonempty judge input.
    check(std::vector<int>(100, 400), 20000);
    std::vector<int> nums;
    int cases = 0;
    for (int length = 0; length <= 7; ++length) enumerate(nums, length, cases);
    assert(cases == 21845);
    std::cout << cases << " arrays matched subset oracle; 6 fixtures, input preservation, 4095 scaling and 6372 single-increase checks passed\n";
}
