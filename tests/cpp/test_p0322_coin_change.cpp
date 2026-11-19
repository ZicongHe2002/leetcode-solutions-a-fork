#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include "../../cpp/p0322_coin_change.cpp"

// Unit-weight shortest paths in the graph of reachable sums.
int bfs_oracle(const std::vector<int>& coins, int target) {
    std::vector<int> distance(target + 1, -1);
    std::queue<int> pending;
    pending.push(0);
    distance[0] = 0;
    while (!pending.empty()) {
        const int sum = pending.front();
        pending.pop();
        if (sum == target) return distance[sum];
        for (int coin : coins) {
            if (coin > target - sum) continue;
            const int next = sum + coin;
            if (distance[next] == -1) {
                distance[next] = distance[sum] + 1;
                pending.push(next);
            }
        }
    }
    return -1;
}

void check(std::vector<int> coins, int amount, int expected) {
    const auto before = coins;
    assert(Solution().coinChange(coins, amount) == expected);
    assert(coins == before);
}

int main() {
    check({1, 3, 4}, 6, 2); // Greedy choosing 4 first is not optimal.
    check({2}, 3, -1);
    check({5, 2}, 0, 0);
    check({2}, 10000, 5000);
    check({2}, 9999, -1);
    check({INT_MAX}, 1, -1);
    check({INT_MAX, 1}, 10000, 10000);
    int cases = 0;
    for (unsigned mask = 1; mask < (1u << 7); ++mask) {
        std::vector<int> coins;
        for (int i = 0; i < 7; ++i) if (mask & (1u << i)) coins.push_back(i + 1);
        for (int amount = 0; amount <= 30; ++amount) {
            const int expected = bfs_oracle(coins, amount);
            check(coins, amount, expected);
            auto reversed = coins;
            std::reverse(reversed.begin(), reversed.end());
            check(reversed, amount, expected);
            auto duplicated = coins;
            duplicated.push_back(coins.front());
            check(duplicated, amount, expected);
            ++cases;
        }
    }
    assert(cases == 3937);
    std::cout << cases << " cases matched BFS oracle; 7 fixtures, input preservation and 7874 permutation/duplicate checks passed\n";
}
