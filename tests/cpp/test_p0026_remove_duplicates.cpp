#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <vector>
#include "../../cpp/p0026_remove_duplicates.cpp"

void check(std::vector<int> values) {
    const std::set<int> distinct(values.begin(), values.end());
    const std::vector<int> expected(distinct.begin(), distinct.end());
    const auto size = values.size();
    const int* const data = values.data();
    const int count = Solution().removeDuplicates(values);
    assert(count == static_cast<int>(expected.size()));
    assert(values.size() == size && values.data() == data);
    assert(std::equal(expected.begin(), expected.end(), values.begin()));
    // Only the returned prefix is a sorted input for a second call.
    std::vector<int> prefix(values.begin(), values.begin() + count);
    const int* const prefixData = prefix.data();
    assert(Solution().removeDuplicates(prefix) == count);
    assert(prefix == expected && prefix.size() == expected.size());
    assert(prefix.data() == prefixData);
    // Intentionally do not impose a condition on the unspecified tail.
}

void enumerate(std::vector<int>& values, int minimum, int remaining, int& cases) {
    if (!remaining) {
        check(values);
        auto mapped = values;
        for (int& value : mapped) value = 2 * value + 1;
        const int* const mappedData = mapped.data();
        const std::set<int> unique(values.begin(), values.end());
        std::vector<int> expected;
        for (int value : unique) expected.push_back(2 * value + 1);
        const int count = Solution().removeDuplicates(mapped);
        assert(count == static_cast<int>(expected.size()));
        assert(std::equal(expected.begin(), expected.end(), mapped.begin()));
        assert(mapped.size() == values.size() && mapped.data() == mappedData);
        ++cases;
        return;
    }
    for (int value = minimum; value <= 2; ++value) {
        values.push_back(value);
        enumerate(values, value, remaining - 1, cases);
        values.pop_back();
    }
}

int main() {
    check({-2, -2, 0, 0, 2});
    int cases = 0;
    std::vector<int> values;
    for (int length = 0; length <= 8; ++length) enumerate(values, -2, length, cases);
    assert(cases == 1287);
    check(std::vector<int>(30000, -100));
    std::vector<int> boundary;
    for (int value = -100; value <= 100; ++value) boundary.push_back(value);
    check(boundary);
    std::cout << "1287 sorted arrays matched set oracle; 3 fixtures, valid-prefix idempotence, 1287 strict-mapping checks and storage preservation passed\n";
}
