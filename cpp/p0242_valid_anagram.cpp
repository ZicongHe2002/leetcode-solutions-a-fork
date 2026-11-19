#include <string>
#include <array>
class Solution {
public:
    bool isAnagram(const std::string& s, const std::string& t) {
        if (s.size() != t.size()) return false;
        std::array<int, 26> difference{};
        for (std::size_t i = 0; i < s.size(); ++i) {
            ++difference[s[i] - 'a'];
            --difference[t[i] - 'a'];
        }
        for (int count : difference) if (count != 0) return false;
        return true;
    }
};
