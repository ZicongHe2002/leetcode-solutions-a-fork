#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>
#include "../../cpp/p0035_search_insert.cpp"

void check(std::vector<int> values, int target) {
    const auto before = values;
    const auto expected = std::count_if(values.begin(), values.end(),
                                        [target](int value) { return value < target; });
    assert(Solution().searchInsert(values, target) == expected);
    assert(values == before);
}

int main() {
    std::vector<int> sample{1, 3, 5, 6};
    assert(Solution().searchInsert(sample, 2) == 1);
    assert(Solution().searchInsert(sample, 5) == 2);
    assert(Solution().searchInsert(sample, 7) == 4);
    assert(Solution().searchInsert(sample, 0) == 0);
    int checked = 0;
    for (int mask = 0; mask < (1 << 7); ++mask) {
        std::vector<int> values;
        for (int bit = 0; bit < 7; ++bit)
            if (mask & (1 << bit)) values.push_back(bit - 3);
        for (int target = -4; target <= 4; ++target) {
            check(values, target);
            auto shifted = values;
            for (int& value : shifted) value += 7;
            const auto shiftedBefore = shifted;
            const auto expected = std::count_if(values.begin(), values.end(),
                                               [target](int value) { return value < target; });
            assert(Solution().searchInsert(shifted, target + 7) == expected);
            assert(shifted == shiftedBefore);
            ++checked;
        }
    }
    for (int target : {INT_MIN, -1, 0, 1, INT_MAX}) check({INT_MIN, 0, INT_MAX}, target);
    std::vector<int> boundary(10000);
    for (int i = 0; i < 10000; ++i) boundary[i] = i - 5000;
    for (int target : {-10000, -5000, 0, 4999, 10000}) check(boundary, target);
    assert(checked == 1152);
    std::cout << "1152 subset/target pairs, 4 fixtures and 10 integer/length boundaries passed; 1152 legal translation checks; input unchanged\n";
}
