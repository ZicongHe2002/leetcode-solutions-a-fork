#include "../../cpp/p0703_kth_largest_stream.cpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

void checkLiteralRanks() {
    std::vector<int> none;
    KthLargest maximum(1, none);
    assert(maximum.add(-10000) == -10000);
    assert(maximum.add(10000) == 10000);
    assert(maximum.add(0) == 10000);

    std::vector<int> initial{5, 1, 7};
    KthLargest second(2, initial);
    assert(second.add(6) == 6);
    assert(second.add(-10000) == 6);
    assert(second.add(10000) == 7);
    assert(second.add(7) == 7);
    assert(second.add(10000) == 10000);

    std::vector<int> duplicates{4, 4};
    KthLargest third(3, duplicates);
    assert(third.add(-5) == -5);
    assert(third.add(4) == 4);
    assert(third.add(10000) == 4);
    assert(third.add(10000) == 4);
    assert(third.add(10000) == 10000);
}

void enumerateArrays(std::vector<int>& prefix, std::vector<std::vector<int>>& arrays) {
    arrays.push_back(prefix);
    if (prefix.size() == 4) return;
    for (int value : {-2, 0, 2}) {
        prefix.push_back(value);
        enumerateArrays(prefix, arrays);
        prefix.pop_back();
    }
}

int insertAndFindRank(std::vector<int>& sorted, int value, int k) {
    sorted.insert(std::lower_bound(sorted.begin(), sorted.end(), value), value);
    assert(sorted.size() >= static_cast<std::size_t>(k));
    return sorted[sorted.size() - k];
}

void checkExhaustiveSmallStreams() {
    std::vector<std::vector<int>> arrays;
    std::vector<int> prefix;
    enumerateArrays(prefix, arrays);
    assert(arrays.size() == 121);
    int objects = 0;
    int comparisons = 0;
    for (const auto& initial : arrays) {
        for (int k = 1; k <= static_cast<int>(initial.size()) + 1; ++k) {
            for (const auto& additions : arrays) {
                if (additions.empty()) continue;
                auto input = initial;
                KthLargest actual(k, input);
                auto expected = initial;
                std::sort(expected.begin(), expected.end());
                for (int value : additions) {
                    assert(actual.add(value) == insertAndFindRank(expected, value, k));
                    ++comparisons;
                }
                ++objects;
            }
        }
    }
    assert(objects == 65640);
    assert(comparisons == 233022);
}

void checkLargestInitialSizeAndAddLimit() {
    std::vector<int> initial;
    for (int value = -10000; value < 0; ++value) initial.push_back(value);
    KthLargest actual(10001, initial);
    auto expected = initial;
    for (int index = 0; index < 10000; ++index) {
        const int rank = insertAndFindRank(expected, index, 10001);
        assert(rank == -10000 + index);
        assert(actual.add(index) == rank);
    }
}

void checkTranslatedSmallStreams() {
    std::vector<std::vector<int>> arrays;
    std::vector<int> prefix;
    enumerateArrays(prefix, arrays);
    int objects = 0;
    int comparisons = 0;
    for (int offset : {-7, 11}) {
        for (const auto& initial : arrays) {
            for (int k = 1; k <= static_cast<int>(initial.size()) + 1; ++k) {
                for (const auto& additions : arrays) {
                    if (additions.empty()) continue;
                    auto input = initial;
                    auto shifted = initial;
                    for (int& value : shifted) value += offset;
                    KthLargest original(k, input);
                    KthLargest translated(k, shifted);
                    bool hasPrevious = false;
                    int previous = 0;
                    int calls = 0;
                    for (int value : additions) {
                        const int answer = original.add(value);
                        const int shiftedAnswer = translated.add(value + offset);
                        assert(shiftedAnswer == answer + offset);
                        if (hasPrevious) {
                            assert(answer >= previous);
                            assert(shiftedAnswer >= previous + offset);
                        }
                        previous = answer;
                        hasPrevious = true;
                        ++comparisons;
                        ++calls;
                    }
                    assert(calls <= 10000);
                    ++objects;
                }
            }
        }
    }
    assert(objects == 131280);
    assert(comparisons == 466044);
}

int main() {
    checkLiteralRanks();
    checkExhaustiveSmallStreams();
    checkLargestInitialSizeAndAddLimit();
    checkTranslatedSmallStreams();
    std::cout << "65640 independent streams and 233022 exhaustive add results matched sorted-history oracle; duplicates, extrema and 10000-add boundary passed; 131280 translated stream pairs and 466044 translated outputs plus monotonic thresholds passed\n";
}
