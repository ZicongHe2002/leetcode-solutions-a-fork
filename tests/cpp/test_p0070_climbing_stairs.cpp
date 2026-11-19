#include <cassert>
#include <cstdint>
#include <iostream>
#include "../../cpp/p0070_climbing_stairs.cpp"

// Count sequences by their number of two-step moves, not by a DP recurrence.
std::int64_t choose(int n, int k) {
    std::int64_t value = 1;
    for (int i = 1; i <= k; ++i) value = value * (n - i + 1) / i;
    return value;
}

int main() {
    Solution solution;
    assert(solution.climbStairs(1) == 1);
    assert(solution.climbStairs(2) == 2);
    assert(solution.climbStairs(5) == 8);
    for (int n = 1; n <= 45; ++n) {
        std::int64_t expected = 0;
        for (int twos = 0; 2 * twos <= n; ++twos) expected += choose(n - twos, twos);
        assert(solution.climbStairs(n) == expected);
    }
    assert(solution.climbStairs(45) == 1836311903);
    std::cout << "45 inputs matched combinatorial oracle; 4 explicit fixtures passed\n";
}
