#include <vector>

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        std::size_t left = 0;
        std::size_t right = nums.size();
        while (left < right) {
            const std::size_t middle = left + (right - left) / 2;
            if (nums[middle] < target) {
                left = middle + 1;
            } else if (nums[middle] > target) {
                right = middle;
            } else {
                return static_cast<int>(middle);
            }
        }
        return -1;
    }
};
