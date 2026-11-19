#include <vector>
class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        std::size_t write = 0;
        for (std::size_t read = 0; read < nums.size(); ++read) {
            if (nums[read] != 0) {
                nums[write] = nums[read];
                ++write;
            }
        }
        for (std::size_t index = write; index < nums.size(); ++index) nums[index] = 0;
    }
};
