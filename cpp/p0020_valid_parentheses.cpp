#include <string>

class Solution {
public:
    bool isValid(std::string s) {
        std::string expected;
        for (char symbol : s) {
            switch (symbol) {
                case '(': expected.push_back(')'); break;
                case '[': expected.push_back(']'); break;
                case '{': expected.push_back('}'); break;
                case ')':
                case ']':
                case '}':
                    if (expected.empty() || expected.back() != symbol) {
                        return false;
                    }
                    expected.pop_back();
                    break;
                default:
                    return false;  // Non-bracket input is outside the problem.
            }
        }
        return expected.empty();
    }
};
