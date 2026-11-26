#include "../../cpp/p0155_min_stack.cpp"
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <vector>

struct Operation { bool push; int value; };

void checkSequence(const std::vector<Operation>& operations) {
    MinStack actual;
    std::vector<int> expected;
    int calls = 0;
    for (const auto& operation : operations) {
        if (operation.push) {
            actual.push(operation.value);
            expected.push_back(operation.value);
        } else {
            assert(!expected.empty());
            actual.pop();
            expected.pop_back();
        }
        ++calls;
        if (!expected.empty()) {
            assert(actual.top() == expected.back());
            assert(actual.getMin() == *std::min_element(expected.begin(), expected.end()));
            calls += 2;
        }
    }
    assert(calls <= 30000);
}

void checkSmallValueTranslations(const std::vector<Operation>& operations) {
    for (int offset : {-7, 11}) {
        MinStack original;
        MinStack shifted;
        int balance = 0;
        int callsPerStack = 0;
        for (const auto& operation : operations) {
            if (operation.push) {
                // Only the small-value enumeration calls this property check.
                assert(operation.value >= -1 && operation.value <= 1);
                original.push(operation.value);
                shifted.push(operation.value + offset);
                ++balance;
            } else {
                assert(balance > 0);
                original.pop();
                shifted.pop();
                --balance;
            }
            ++callsPerStack;
            if (balance > 0) {
                assert(shifted.top() == original.top() + offset);
                assert(shifted.getMin() == original.getMin() + offset);
                callsPerStack += 2;
            }
        }
        assert(callsPerStack <= 30000);
    }
}

void enumerate(std::vector<Operation>& operations, int balance, int& sequences) {
    checkSequence(operations);
    checkSmallValueTranslations(operations);
    ++sequences;
    if (operations.size() == 8) return;
    for (int value : {-1,0,1}) {
        operations.push_back({true, value});
        enumerate(operations, balance + 1, sequences);
        operations.pop_back();
    }
    if (balance > 0) {
        operations.push_back({false, 0});
        enumerate(operations, balance - 1, sequences);
        operations.pop_back();
    }
}

int main() {
    MinStack example;
    example.push(-2);
    example.push(0);
    example.push(-3);
    assert(example.getMin() == -3);
    example.pop();
    assert(example.top() == 0 && example.getMin() == -2);
    checkSequence({{true,2},{true,1},{true,1},{false,0},{true,3},
                   {false,0},{false,0},{false,0},{true,-1}});
    checkSequence({{true,2},{true,1},{true,1},{false,0},{false,0},
                   {false,0},{true,7},{true,-1},{false,0},{false,0}});
    checkSequence({{true,INT_MAX},{true,INT_MIN},{true,INT_MIN},
                   {false,0},{false,0},{true,0},{false,0},{false,0}});
    int sequences = 0;
    std::vector<Operation> operations;
    enumerate(operations, 0, sequences);
    assert(sequences == 59236);
    MinStack large;
    int calls = 0;
    for (int value = 5000; value >= 1; --value) {
        large.push(value);
        assert(large.top() == value);
        assert(large.getMin() == value);
        calls += 3;
    }
    for (int removed = 1; removed <= 5000; ++removed) {
        large.pop();
        ++calls;
        if (removed < 5000) {
            assert(large.top() == removed + 1);
            assert(large.getMin() == removed + 1);
            calls += 2;
        }
    }
    assert(calls == 29998);
    std::cout << "59236 legal sequences matched vector/min_element oracle; literal example, duplicate minima and signed-int extremes passed; 29998-call boundary passed; "
              << sequences * 2 << " translated sequence checks passed\n";
}
