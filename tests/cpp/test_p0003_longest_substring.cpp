#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../cpp/p0003_longest_substring.cpp"

// Independent oracle enumerates every start and scans until the first repeat.
int bruteLength(const std::string& text) {
    int best = 0;
    for (std::size_t start = 0; start < text.size(); ++start) {
        std::array<bool, 256> used{};
        for (std::size_t end = start; end < text.size(); ++end) {
            const auto byte = static_cast<unsigned char>(text[end]);
            if (used[byte]) break;
            used[byte] = true;
            best = std::max(best, static_cast<int>(end - start + 1));
        }
    }
    return best;
}

// On 8-bit bytes, multiplication by 5 followed by adding 17 is a permutation.
std::string renameBytes(const std::string& text) {
    std::string renamed;
    renamed.reserve(text.size());
    for (unsigned char byte : text) {
        const auto mapped = static_cast<unsigned char>((5 * byte + 17) % 256);
        renamed.push_back(static_cast<char>(mapped));
    }
    return renamed;
}

int main() {
    // Catches a left boundary moving backwards and substring/subsequence mixups.
    const std::vector<std::pair<std::string, int>> fixtures{
        {"abcabcbb", 3}, {"bbbbb", 1}, {"pwwkew", 3},
        {"abba", 2}, {"tmmzuxt", 5}, {"", 0}, {" ", 1}, {"a b a", 3}
    };
    Solution solver;
    for (const auto& entry : fixtures) {
        assert(solver.lengthOfLongestSubstring(entry.first) == entry.second);
    }
    int renamingChecks = 0;
    int checked = 0;
    int combinations = 1;
    for (int length = 0; length <= 7; ++length) {
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::string text(length, 'a');
            for (char& symbol : text) {
                symbol += value % 3;
                value /= 3;
            }
            const int expected = bruteLength(text);
            assert(solver.lengthOfLongestSubstring(text) == expected);
            const auto renamed = renameBytes(text);
            assert(bruteLength(renamed) == expected);
            assert(solver.lengthOfLongestSubstring(renamed) == expected);
            ++renamingChecks;
            ++checked;
        }
        combinations *= 3;
    }
    assert(checked == 3280);
    assert(renamingChecks == 3280);
    // Explicit byte-string extension: high-bit bytes must not index negatively.
    const std::string bytes{static_cast<char>(255), 'a', static_cast<char>(255)};
    assert(solver.lengthOfLongestSubstring(bytes) == 2);
    assert(solver.lengthOfLongestSubstring(std::string("a\0b\0", 4)) == 3);
    // UTF-8 for two repeated e-acute code points: 2 distinct bytes, 1 code point.
    const std::string utf8("\xC3\xA9\xC3\xA9", 4);
    assert(solver.lengthOfLongestSubstring(utf8) == 2);
    std::cout << "Longest substring: 8 fixtures, 3280 exhaustive strings, 2 byte extensions, 3280 renaming checks and UTF-8 byte example passed\n";
}
