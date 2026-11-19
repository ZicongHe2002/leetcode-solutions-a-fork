#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value = 0) : val(value), next(nullptr) {}
};
#include "../../cpp/p0206_reverse_linked_list.cpp"

void checkReversal(const std::vector<int>& values) {
    std::vector<std::unique_ptr<ListNode>> storage;
    for (int value : values) storage.push_back(std::make_unique<ListNode>(value));
    for (std::size_t i = 1; i < storage.size(); ++i) storage[i-1]->next = storage[i].get();
    ListNode* head = storage.empty() ? nullptr : storage.front().get();
    Solution solver;
    ListNode* result = solver.reverseList(head);
    ListNode* cursor = result;
    // Use identity as well as values so equal-valued nodes cannot hide a copy.
    for (std::size_t i = values.size(); i > 0; --i) {
        assert(cursor == storage[i-1].get());
        assert(cursor->val == values[i-1]);
        cursor = cursor->next;
    }
    assert(cursor == nullptr);
    cursor = solver.reverseList(result);
    assert(cursor == head);
    for (std::size_t i = 0; i < values.size(); ++i) {
        assert(cursor == storage[i].get());
        assert(cursor->val == values[i]);
        cursor = cursor->next;
    }
    assert(cursor == nullptr);
}

int main() {
    int combinations = 1;
    int checked = 0;
    for (int length = 0; length <= 6; ++length) {
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::vector<int> values(length);
            for (int& item : values) { item = value % 3 - 1; value /= 3; }
            checkReversal(values);
            ++checked;
        }
        combinations *= 3;
    }
    assert(checked == 1093);
    std::vector<int> longValues(5000);
    for (std::size_t i = 0; i < longValues.size(); ++i) longValues[i] = static_cast<int>(i % 3) - 1;
    checkReversal(longValues);
    std::cout << "Reverse list: 1093 small lists and a 5000-node list preserve identities/values and restore on second reversal\n";
}
