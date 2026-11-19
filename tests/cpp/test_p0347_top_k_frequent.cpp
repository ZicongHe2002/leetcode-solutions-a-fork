#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>
#include "../../cpp/p0347_top_k_frequent.cpp"

void exact(std::vector<int> values, int k, std::vector<int> expected) {
    const auto before = values;
    auto result = Solution().topKFrequent(values, k);
    std::sort(result.begin(), result.end());
    std::sort(expected.begin(), expected.end());
    assert(result == expected);
    assert(values == before);
    std::reverse(values.begin(), values.end());
    const auto reversedBefore = values;
    auto reversedResult = Solution().topKFrequent(values, k);
    std::sort(reversedResult.begin(), reversedResult.end());
    assert(reversedResult == expected);
    assert(values == reversedBefore);
}

void checkAllValidCutoffs(const std::vector<int>& values, int& count) {
    std::map<int, int> frequency;
    for (int value : values) ++frequency[value];
    std::vector<std::pair<int, int>> ordered;
    for (const auto& entry : frequency) ordered.push_back({entry.second, entry.first});
    std::sort(ordered.begin(), ordered.end(), [](const auto& a, const auto& b) {
        return a.first != b.first ? a.first > b.first : a.second < b.second;
    });
    for (std::size_t k = 1; k <= ordered.size(); ++k) {
        // A tie across the cutoff violates the problem's unique-answer guarantee.
        if (k < ordered.size() && ordered[k - 1].first == ordered[k].first) continue;
        std::vector<int> expected;
        for (std::size_t i = 0; i < k; ++i) expected.push_back(ordered[i].second);
        exact(values, static_cast<int>(k), expected);
        auto doubled = values;
        doubled.insert(doubled.end(), values.begin(), values.end());
        exact(doubled, static_cast<int>(k), expected);
        ++count;
    }
}

void enumerate(std::vector<int>& values, int remaining, int& count) {
    if (!remaining) { checkAllValidCutoffs(values, count); return; }
    for (int value : {-1, 0, 1}) {
        values.push_back(value);
        enumerate(values, remaining - 1, count);
        values.pop_back();
    }
}

int main() {
    exact({1, 1, 1, 2, 2, 3}, 2, {1, 2});
    exact({-1, -1}, 1, {-1});
    exact({4, 5}, 2, {4, 5});
    exact({-10000, 10000, -10000}, 1, {-10000});
    int checked = 0;
    std::vector<int> values;
    for (int length = 1; length <= 7; ++length) enumerate(values, length, checked);
    assert(checked >= 3279);
    std::vector<int> boundary(60000, 7);
    boundary.insert(boundary.end(), 30000, 8);
    boundary.insert(boundary.end(), 10000, 9);
    exact(boundary, 2, {7, 8});
    std::cout << checked << " unique-cutoff cases matched ordered-frequency oracle; frequency-doubling and reversal checks; 4 fixtures and 100000-length boundary passed\n";
}
