#include <vector>
class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int>& nums) {
        std::vector<int> result(nums.size());
        std::size_t left = 0;
        std::size_t right = nums.size();
        for (std::size_t write = nums.size(); write > 0; --write) {
            const int leftSquare = nums[left] * nums[left];
            const int rightSquare = nums[right - 1] * nums[right - 1];
            if (leftSquare > rightSquare) {
                result[write - 1] = leftSquare;
                ++left;
            } else {
                result[write - 1] = rightSquare;
                --right;
            }
        }
        return result;
    }
};
