#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "../../cpp/p0242_valid_anagram.cpp"

void enumerate(std::string& value, int remaining, std::vector<std::string>& all) {
    if (!remaining) { all.push_back(value); return; }
    for (char ch : {'a', 'b', 'c'}) {
        value.push_back(ch);
        enumerate(value, remaining - 1, all);
        value.pop_back();
    }
}

int main() {
    assert(Solution().isAnagram("anagram", "nagaram"));
    assert(!Solution().isAnagram("rat", "car"));
    assert(!Solution().isAnagram("aacc", "ccac"));
    std::vector<std::string> all;
    std::string value;
    for (int length = 0; length <= 5; ++length) enumerate(value, length, all);
    assert(all.size() == 364);
    int checked = 0;
    for (const auto& first : all) for (const auto& second : all) {
        auto sortedFirst = first;
        auto sortedSecond = second;
        std::sort(sortedFirst.begin(), sortedFirst.end());
        std::sort(sortedSecond.begin(), sortedSecond.end());
        const bool expected = sortedFirst == sortedSecond;
        assert(Solution().isAnagram(first, second) == expected);
        assert(Solution().isAnagram(second, first) == expected);
        const auto suffixedFirst = first + 'z';
        const auto suffixedSecond = second + 'z';
        assert(Solution().isAnagram(suffixedFirst, suffixedSecond) == expected);
        ++checked;
    }
    assert(checked == 132496);
    const std::string boundary(50000, 'z');
    assert(Solution().isAnagram(boundary, boundary));
    auto mismatch = boundary;
    mismatch.front() = 'a';
    assert(!Solution().isAnagram(boundary, mismatch));
    assert(!Solution().isAnagram(boundary, boundary.substr(1)));
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    assert(Solution().isAnagram(alphabet, std::string(alphabet.rbegin(), alphabet.rend())));
    std::cout << "132496 string pairs matched sorting oracle; 132496 symmetry and same-suffix checks; 3 fixtures and 4 alphabet/length boundaries passed\n";
}
