#include <vector>
#include <unordered_map>
class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> frequency;
        for (int value : nums) ++frequency[value];
        std::vector<std::vector<int>> buckets(nums.size() + 1);
        for (const auto& entry : frequency) buckets[entry.second].push_back(entry.first);
        std::vector<int> result;
        result.reserve(static_cast<std::size_t>(k));
        for (std::size_t count = nums.size(); count > 0; --count) {
            for (int value : buckets[count]) {
                result.push_back(value);
                if (result.size() == static_cast<std::size_t>(k)) return result;
            }
        }
        return result;
    }
};
