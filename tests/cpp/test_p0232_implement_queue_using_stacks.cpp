#include "../../cpp/p0232_implement_queue_using_stacks.cpp"
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

struct Operation { bool push; int value; };

void checkSequence(const std::vector<Operation>& operations) {
    MyQueue actual;
    std::deque<int> expected;
    int calls = 1;
    assert(actual.empty());
    for (const auto& operation : operations) {
        if (operation.push) {
            actual.push(operation.value);
            expected.push_back(operation.value);
        } else {
            assert(!expected.empty());
            assert(actual.pop() == expected.front());
            expected.pop_front();
        }
        ++calls;
        assert(actual.empty() == expected.empty());
        ++calls;
        if (!expected.empty()) {
            assert(actual.peek() == expected.front());
            assert(actual.peek() == expected.front());
            calls += 2;
        }
    }
    assert(calls <= 100);
}

void checkRenamedSequence(const std::vector<Operation>& operations);

void enumerate(std::vector<Operation>& operations, int balance, int& sequences) {
    checkSequence(operations);
    checkRenamedSequence(operations);
    ++sequences;
    if (operations.size() == 8) return;
    for (int value : {1, 2, 9}) {
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

void checkMixedTransferAndReuse() {
    MyQueue queue;
    queue.push(1);
    queue.push(2);
    assert(queue.peek() == 1);
    assert(queue.peek() == 1);
    assert(queue.pop() == 1);
    queue.push(9);
    assert(queue.peek() == 2);
    assert(queue.pop() == 2);
    assert(queue.pop() == 9);
    assert(queue.empty());
    queue.push(2);
    assert(queue.peek() == 2);
    assert(queue.pop() == 2);
    assert(queue.empty());
}

void checkHundredCallBoundary() {
    MyQueue queue;
    int calls = 1;
    assert(queue.empty());
    for (int index = 0; index < 25; ++index) {
        queue.push(1 + index % 9);
        ++calls;
    }
    for (int index = 0; index < 24; ++index) {
        assert(queue.peek() == 1 + index % 9);
        assert(queue.pop() == 1 + index % 9);
        calls += 2;
    }
    assert(queue.peek() == 7);
    assert(queue.pop() == 7);
    assert(queue.empty());
    queue.push(9);
    assert(queue.peek() == 9);
    assert(queue.pop() == 9);
    assert(queue.empty());
    calls += 7;
    for (int count = 0; count < 19; ++count) {
        assert(queue.empty());
        ++calls;
    }
    assert(calls == 100);
}

void checkRenamedSequence(const std::vector<Operation>& operations) {
    for (int mapping = 0; mapping < 2; ++mapping) {
        const auto rename = [mapping](int value) {
            return mapping == 0 ? 10 - value : value % 9 + 1;
        };
        MyQueue original;
        MyQueue renamed;
        int calls = 1;
        assert(original.empty() && renamed.empty());
        for (const auto& operation : operations) {
            if (operation.push) {
                original.push(operation.value);
                renamed.push(rename(operation.value));
            } else {
                assert(renamed.pop() == rename(original.pop()));
            }
            ++calls;
            const bool isEmpty = original.empty();
            assert(renamed.empty() == isEmpty);
            ++calls;
            if (!isEmpty) {
                assert(renamed.peek() == rename(original.peek()));
                assert(renamed.peek() == rename(original.peek()));
                calls += 2;
            }
        }
        assert(calls <= 100);
    }
}

int main() {
    checkMixedTransferAndReuse();
    std::vector<Operation> operations;
    int sequences = 0;
    enumerate(operations, 0, sequences);
    assert(sequences == 59236);
    checkHundredCallBoundary();
    std::cout << "59236 legal sequences matched deque oracle; repeated peek, mixed transfer, reuse and exact 100-call boundary passed; 118472 bijective value-renaming sequence pairs passed\n";
}
