#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "../../cpp/p0053_maximum_subarray.cpp"

int bruteSum(const std::vector<int>& values) {
    int best = values.front();
    for (std::size_t start = 0; start < values.size(); ++start) {
        int sum = 0;
        for (std::size_t end = start; end < values.size(); ++end) {
            sum += values[end];
            best = std::max(best, sum);
        }
    }
    return best;
}

void check(std::vector<int> values, int expected) {
    const auto original = values;
    assert(Solution{}.maxSubArray(values) == expected);
    assert(values == original);
}

int main() {
    // Catches allowing the empty subarray and returning only the final ending.
    check({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);
    check({-5, -2, -7}, -2);
    check({4, -6, 3, 2, -1}, 5);
    check({1}, 1);
    check({0, 0}, 0);
    check({5, 4, -1, 7, 8}, 23);
    int combinations = 1;
    int reversalChecks = 0;
    int checked = 0;
    for (int length = 1; length <= 6; ++length) {
        combinations *= 5;
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::vector<int> values(length);
            for (int& item : values) {
                item = value % 5 - 2;
                value /= 5;
            }
            const int expected = bruteSum(values);
            check(values, expected);
            auto reversed = values;
            std::reverse(reversed.begin(), reversed.end());
            check(reversed, expected);
            ++reversalChecks;
            ++checked;
        }
    }
    assert(checked == 19530);
    assert(reversalChecks == 19530);
    check(std::vector<int>(100000, 10000), 1000000000);
    check(std::vector<int>(100000, -10000), -10000);
    std::vector<int> empty;
    bool threw = false;
    try { Solution{}.maxSubArray(empty); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    std::cout << "Maximum subarray: 6 fixtures, 19530 exhaustive arrays, 2 limits, empty-input exception and 19530 reversal checks passed\n";
}
