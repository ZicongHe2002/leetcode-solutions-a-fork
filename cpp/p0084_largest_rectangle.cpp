#include <algorithm>
#include <utility>
#include <vector>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        std::vector<std::pair<int, int>> pending;
        const int n = static_cast<int>(heights.size());
        int best = 0;
        for (int right = 0; right <= n; ++right) {
            const int height = right == n ? 0 : heights[right];
            int left = right;
            while (!pending.empty() && pending.back().first > height) {
                const auto [previousHeight, start] = pending.back();
                pending.pop_back();
                best = std::max(best, previousHeight * (right - start));
                left = start;
            }
            if (right < n && (pending.empty() || pending.back().first < height)) {
                pending.emplace_back(height, left);
            }
        }
        return best;
    }
};
