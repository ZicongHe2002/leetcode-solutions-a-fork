#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "../../cpp/p0020_valid_parentheses.cpp"


// Repeatedly removes adjacent legal pairs; independent of the stack algorithm.
bool eliminationOracle(std::string text) {
    const std::vector<std::string> pairs{"()", "[]", "{}"};
    while (true) {
        const auto before = text.size();
        for (const auto& pair : pairs) {
            auto position = text.find(pair);
            while (position != std::string::npos) {
                text.erase(position, pair.size());
                position = text.find(pair);
            }
        }
        if (text.size() == before) {
            return text.empty();
        }
    }
}

int main() {
    // Catches count-only validation, incorrect LIFO matching, and stale state.
    const std::vector<std::pair<std::string, bool>> cases{
        {"()", true}, {"()[]{}", true}, {"(]", false},
        {"([])", true}, {"([)]", false}, {"{[()]}", true},
        {"(", false}, {")", false}, {"(()", false},
        {"())", false}, {")(", false}, {"((()))", true},
        {"", true}, {"a", false}
    };
    Solution solver;
    for (const auto& entry : cases) {
        assert(solver.isValid(entry.first) == entry.second);
    }
    const std::string deep(5000, '(');
    assert(solver.isValid(deep + std::string(5000, ')')));
    assert(!solver.isValid(deep + std::string(4999, ')')));
    const std::string alphabet = "()[]{}";
    int checked = 0;
    int combinations = 1;
    for (int length = 0; length <= 6; ++length) {
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::string text(length, '(');
            for (char& symbol : text) {
                symbol = alphabet[value % 6];
                value /= 6;
            }
            assert(solver.isValid(text) == eliminationOracle(text));
            ++checked;
        }
        combinations *= 6;
    }
    assert(checked == 55987);
    std::cout << "Parentheses: 14 fixtures, 2 depth cases and 55987 elimination-oracle checks passed\n";
}
