#include <algorithm>
#include <stdexcept>
#include <vector>

class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        if (nums.empty()) {
            throw std::invalid_argument("a nonempty array is required");
        }
        int ending = nums.front();
        int best = ending;
        for (std::size_t i = 1; i < nums.size(); ++i) {
            ending = std::max(nums[i], ending + nums[i]);
            best = std::max(best, ending);
        }
        return best;
    }
};
