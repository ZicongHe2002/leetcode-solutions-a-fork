#include <stdexcept>
#include <vector>
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        int left = 0;
        int right = static_cast<int>(numbers.size()) - 1;
        while (left < right) {
            const long long total = static_cast<long long>(numbers[left]) + numbers[right];
            if (total == target) return {left + 1, right + 1};
            if (total < target) ++left;
            else --right;
        }
        throw std::invalid_argument("No pair of distinct indices sums to target");
    }
};
