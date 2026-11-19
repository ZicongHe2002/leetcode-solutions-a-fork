#include <algorithm>
#include <vector>

class Solution {
public:
    int rob(std::vector<int>& nums) {
        int two_back = 0;
        int one_back = 0;
        for (int value : nums) {
            const int current = std::max(one_back, two_back + value);
            two_back = one_back;
            one_back = current;
        }
        return one_back;
    }
};
