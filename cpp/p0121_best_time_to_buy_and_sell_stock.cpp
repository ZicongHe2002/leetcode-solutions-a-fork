#include <algorithm>
#include <vector>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        int minimum = prices.front();
        int best = 0;
        for (std::size_t day = 1; day < prices.size(); ++day) {
            // minimum refers only to days strictly before this selling day.
            best = std::max(best, prices[day] - minimum);
            minimum = std::min(minimum, prices[day]);
        }
        return best;
    }
};
