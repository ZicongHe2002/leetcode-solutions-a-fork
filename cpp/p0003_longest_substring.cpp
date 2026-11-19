#include <algorithm>
#include <array>
#include <string>

class Solution {
public:
    int lengthOfLongestSubstring(const std::string& s) {
        std::array<int, 256> latest;
        latest.fill(-1);
        int left = 0;
        int best = 0;
        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            const auto byte = static_cast<unsigned char>(s[right]);
            left = std::max(left, latest[byte] + 1);
            latest[byte] = right;
            best = std::max(best, right - left + 1);
        }
        return best;
    }
};
