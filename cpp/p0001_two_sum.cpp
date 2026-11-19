#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<long long, int> seen;
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            const long long need = static_cast<long long>(target) - nums[i];
            const auto match = seen.find(need);
            if (match != seen.end()) {
                return {match->second, i};
            }
            // Insert after lookup so the current index cannot match itself.
            seen.emplace(nums[i], i);
        }
        return {};  // Outside the problem's guaranteed-one-solution contract.
    }
};
