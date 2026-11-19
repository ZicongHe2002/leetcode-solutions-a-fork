#include <algorithm>
#include <vector>

class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        const int unreachable = amount + 1;
        std::vector<int> best(amount + 1, unreachable);
        best[0] = 0;
        for (int value = 1; value <= amount; ++value) {
            for (int coin : coins) {
                if (coin <= value && best[value - coin] != unreachable) {
                    best[value] = std::min(best[value], best[value - coin] + 1);
                }
            }
        }
        return best[amount] == unreachable ? -1 : best[amount];
    }
};
