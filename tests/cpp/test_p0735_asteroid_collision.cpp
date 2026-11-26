#include "../../cpp/p0735_asteroid_collision.cpp"
#include <cassert>
#include <iostream>
#include <vector>

void exact(std::vector<int> input, const std::vector<int>& expected) {
    const auto before = input;
    assert(Solution().asteroidCollision(input) == expected);
    assert(input == before);
}

std::vector<int> eraseCollisions(std::vector<int> values, bool rightmost) {
    while (true) {
        int collision = -1;
        for (int index = 0; index + 1 < static_cast<int>(values.size()); ++index) {
            if (values[index] > 0 && values[index + 1] < 0) {
                collision = index;
                if (!rightmost) break;
            }
        }
        if (collision < 0) return values;
        const int rightward = values[collision];
        const int leftwardSize = -values[collision + 1];
        if (rightward == leftwardSize) {
            values.erase(values.begin() + collision, values.begin() + collision + 2);
        } else if (rightward < leftwardSize) {
            values.erase(values.begin() + collision);
        } else {
            values.erase(values.begin() + collision + 1);
        }
    }
}

std::vector<int> mirror(const std::vector<int>& values) {
    std::vector<int> result;
    result.reserve(values.size());
    for (auto item = values.rbegin(); item != values.rend(); ++item) {
        result.push_back(-*item);
    }
    return result;
}

void checkSymmetries(const std::vector<int>& input, const std::vector<int>& survivors) {
    exact(mirror(input), mirror(survivors));
    for (int factor : {2, 7, 333}) {
        auto scaled = input;
        auto expected = survivors;
        for (int& value : scaled) {
            value *= factor;
            assert(value != 0 && value >= -1000 && value <= 1000);
        }
        for (int& value : expected) value *= factor;
        exact(scaled, expected);
    }
}

void enumerate(std::vector<int>& input, int& count) {
    if (input.size() >= 2) {
        const auto leftFirst = eraseCollisions(input, false);
        assert(leftFirst == eraseCollisions(input, true));
        exact(input, leftFirst);
        checkSymmetries(input, leftFirst);
        ++count;
    }
    if (input.size() == 8) return;
    for (int value : {-3, -1, 1, 3}) {
        input.push_back(value);
        enumerate(input, count);
        input.pop_back();
    }
}

void checkLiteralCollisions() {
    exact({-2, -1, 1, 2}, {-2, -1, 1, 2});
    exact({6, 2, -2}, {6});
    exact({6, 1, -3}, {6});
    exact({1, 2, -4}, {-4});
    exact({3, -3, -2}, {-2});
    exact({4, -4}, {});
    exact({-1000, 1000}, {-1000, 1000});
    exact({1000, -1000}, {});
    exact({-3, -1, -2}, {-3, -1, -2});
    exact({3, 1, 2}, {3, 1, 2});
    exact({7, -2, -7, 4, -5, 6}, {-5, 6});
    exact({8, 3, 1, -4, -8, -2, 5}, {-2, 5});
}

void checkMaximumLengths() {
    std::vector<int> sameDirection(10000, -1000);
    exact(sameDirection, sameDirection);
    std::vector<int> separated(5000, -1000);
    separated.insert(separated.end(), 5000, 1000);
    exact(separated, separated);
    std::vector<int> cancel(5000, 1000);
    cancel.insert(cancel.end(), 5000, -1000);
    exact(cancel, {});
    std::vector<int> cascade(9999, 1);
    cascade.push_back(-1000);
    exact(cascade, {-1000});
    std::vector<int> blocked(10000, -1);
    blocked.front() = 1000;
    exact(blocked, {1000});
}

int main() {
    checkLiteralCollisions();
    std::vector<int> input;
    int count = 0;
    enumerate(input, count);
    assert(count == 87376);
    checkMaximumLengths();
    std::cout << "87376 arrays matched both adjacent-erasure orders; 12 literal cases and 5 length-10000 boundaries passed; input unchanged; 87376 mirrors and 262128 positive-scale cases passed\n";
}
