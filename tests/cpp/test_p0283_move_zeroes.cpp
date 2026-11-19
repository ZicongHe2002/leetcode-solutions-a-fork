#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <iterator>
#include <vector>
#include "../../cpp/p0283_move_zeroes.cpp"

std::vector<int> check(std::vector<int> values) {
    std::vector<int> expected;
    std::copy_if(values.begin(), values.end(), std::back_inserter(expected), [](int v) { return v != 0; });
    expected.insert(expected.end(), std::count(values.begin(), values.end(), 0), 0);
    const int* const data = values.data();
    const auto size = values.size();
    Solution().moveZeroes(values);
    assert(values == expected);
    assert(values.size() == size && values.data() == data);
    Solution().moveZeroes(values);
    assert(values == expected);
    assert(values.size() == size && values.data() == data);
    return values;
}

void enumerate(std::vector<int>& values, int remaining, int& cases) {
    if (!remaining) {
        auto expectedWithExtraZero = check(values);
        expectedWithExtraZero.push_back(0);
        auto prefixed = values;
        prefixed.insert(prefixed.begin(), 0);
        assert(check(prefixed) == expectedWithExtraZero);
        auto suffixed = values;
        suffixed.push_back(0);
        assert(check(suffixed) == expectedWithExtraZero);
        ++cases;
        return;
    }
    for (int value : {-1, 0, 2}) {
        values.push_back(value);
        enumerate(values, remaining - 1, cases);
        values.pop_back();
    }
}

int main() {
    check({0, 2, 0, -1, 2, 0});
    int cases = 0;
    std::vector<int> values;
    for (int length = 0; length <= 7; ++length) enumerate(values, length, cases);
    assert(cases == 3280);
    check({INT_MIN, 0, INT_MAX, 0, INT_MIN});
    check(std::vector<int>(10000, 0));
    check(std::vector<int>(10000, -1));
    std::vector<int> alternating(10000);
    for (int i = 0; i < 10000; ++i) alternating[i] = i % 2 == 0 ? 0 : i;
    check(alternating);
    std::cout << "3280 arrays matched filter/count oracle; 5 fixtures, 6560 zero-padding checks, idempotence and storage preservation passed\n";
}
