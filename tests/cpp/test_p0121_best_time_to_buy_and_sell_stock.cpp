#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "../../cpp/p0121_best_time_to_buy_and_sell_stock.cpp"

// Independent O(n^2) oracle: explicitly enumerates buy-before-sell choices.
int bruteProfit(const std::vector<int>& prices) {
    int best = 0;
    for (std::size_t buy = 0; buy < prices.size(); ++buy) {
        for (std::size_t sell = buy + 1; sell < prices.size(); ++sell) {
            best = std::max(best, prices[sell] - prices[buy]);
        }
    }
    return best;
}

void checkProfit(std::vector<int> prices, int expected) {
    const auto original = prices;
    assert(Solution{}.maxProfit(prices) == expected);
    assert(prices == original);
}

int main() {
    // Catches future-minimum use, summing multiple trades, and negative results.
    checkProfit({7, 1, 5, 3, 6, 4}, 5);
    checkProfit({7, 6, 4, 3, 1}, 0);
    checkProfit({1, 2, 3, 4}, 3);
    checkProfit({2, 2, 2}, 0);
    checkProfit({5}, 0);
    checkProfit({2, 4, 1}, 2);
    checkProfit({0, 10000}, 10000);
    checkProfit({}, 0);  // Explicit extension beyond nonempty official input.

    const std::vector<int> scales{0, 1, 3};
    const std::vector<int> offsets{0, 11, 1000};
    int propertyChecks = 0;
    int checked = 0;
    int combinations = 1;
    for (int length = 0; length <= 6; ++length) {
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::vector<int> prices(length);
            for (int& price : prices) {
                price = value % 4;
                value /= 4;
            }
            const int expected = bruteProfit(prices);
            checkProfit(prices, expected);
            if (!prices.empty()) {
                for (int scale : scales) {
                    for (int offset : offsets) {
                        std::vector<int> transformed;
                        transformed.reserve(prices.size());
                        for (int price : prices) {
                            const int changed = scale * price + offset;
                            assert(0 <= changed && changed <= 10000);
                            transformed.push_back(changed);
                        }
                        checkProfit(transformed, scale * expected);
                        ++propertyChecks;
                    }
                }
            }
            ++checked;
        }
        combinations *= 4;
    }
    assert(checked == 5461);
    assert(propertyChecks == 49140);
    std::cout << "Stock: 8 fixtures, 5461 exhaustive arrays and 49140 affine-property checks passed\n";
}
