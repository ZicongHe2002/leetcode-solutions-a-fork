#include <vector>
class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0;
        std::size_t write = 1;
        for (std::size_t read = 1; read < nums.size(); ++read) {
            if (nums[read] != nums[write - 1]) {
                nums[write] = nums[read];
                ++write;
            }
        }
        return static_cast<int>(write);
    }
};
