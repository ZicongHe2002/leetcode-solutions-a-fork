#include "../../cpp/p0084_largest_rectangle.cpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

void exact(std::vector<int> input, int expected) {
    const auto before = input;
    assert(Solution().largestRectangleArea(input) == expected);
    assert(input == before);
}

// Enumerate every contiguous interval; no stack or boundary reuse.
int intervalOracle(const std::vector<int>& heights) {
    int best = 0;
    for (int left = 0; left < static_cast<int>(heights.size()); ++left) {
        int minimum = heights[left];
        for (int right = left; right < static_cast<int>(heights.size()); ++right) {
            minimum = std::min(minimum, heights[right]);
            best = std::max(best, minimum * (right - left + 1));
        }
    }
    return best;
}

void checkSymmetries(const std::vector<int>& heights, int expected) {
    auto reversed = heights;
    std::reverse(reversed.begin(), reversed.end());
    exact(reversed, expected);
    for (int factor : {2, 7, 2500}) {
        auto scaled = heights;
        for (int& value : scaled) {
            value *= factor;
            assert(value >= 0 && value <= 10000);
        }
        exact(scaled, expected * factor);
    }
}

void enumerate(std::vector<int>& heights, int& checked) {
    if (!heights.empty()) {
        const int expected = intervalOracle(heights);
        exact(heights, expected);
        checkSymmetries(heights, expected);
        ++checked;
    }
    if (heights.size() == 8) return;
    for (int value : {0, 1, 3, 4}) {
        heights.push_back(value);
        enumerate(heights, checked);
        heights.pop_back();
    }
}

void checkLiteralRectangles() {
    exact({3}, 3);
    exact({0}, 0);
    exact({10000}, 10000);
    exact({3, 3, 3, 3}, 12);
    exact({3, 1, 3}, 3);
    exact({1, 3, 2, 4, 2}, 8);
    exact({4, 2, 2, 1}, 6);
    exact({1, 2, 3, 4}, 6);
    exact({4, 3, 2, 1}, 6);
    exact({4, 0, 4, 4}, 8);
    exact({2, 4, 2, 4, 2}, 10);
    exact({0, 0, 0}, 0);
    exact({4, 4, 1, 4, 4}, 8);
    exact({2, 5, 2, 4, 1}, 8);
}

void checkLargeInputs() {
    exact(std::vector<int>(100000, 10000), 1000000000);
    exact(std::vector<int>(100000, 0), 0);
    exact(std::vector<int>(100000, 1), 100000);
    std::vector<int> split(100000, 10000);
    split[49999] = 0;
    exact(split, 500000000);
    std::vector<int> alternating(100000, 0);
    for (int i = 0; i < 100000; i += 2) alternating[i] = 10000;
    exact(alternating, 10000);
    std::vector<int> increasing(10000);
    for (int i = 0; i < 10000; ++i) increasing[i] = i + 1;
    exact(increasing, 25005000);
    std::reverse(increasing.begin(), increasing.end());
    exact(increasing, 25005000);
}

int main() {
    checkLiteralRectangles();
    int checked = 0;
    std::vector<int> heights;
    enumerate(heights, checked);
    assert(checked == 87380);
    checkLargeInputs();
    std::cout << "87380 arrays matched interval oracle; 14 literal cases and 7 large boundaries passed; input unchanged; 87380 reversals and 262140 legal height scalings passed\n";
}
