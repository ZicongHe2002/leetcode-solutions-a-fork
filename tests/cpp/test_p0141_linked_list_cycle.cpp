#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value = 0) : val(value), next(nullptr) {}
};
#include "../../cpp/p0141_linked_list_cycle.cpp"

bool visitedOracle(ListNode* head) {
    std::unordered_set<ListNode*> visited;
    while (head != nullptr) {
        if (!visited.insert(head).second) return true;
        head = head->next;
    }
    return false;
}

void checkStructure(int length, int entry) {
    Solution solver;
    std::vector<std::unique_ptr<ListNode>> storage;
    for (int i = 0; i < length; ++i) storage.push_back(std::make_unique<ListNode>(7));
    for (int i = 1; i < length; ++i) storage[i-1]->next = storage[i].get();
    if (entry >= 0) storage.back()->next = storage[entry].get();
    std::vector<ListNode*> originalNext;
    for (const auto& node : storage) originalNext.push_back(node->next);
    ListNode* head = storage.empty() ? nullptr : storage.front().get();
    const bool expected = visitedOracle(head);
    assert(expected == (entry >= 0));
    // Equal values must not be mistaken for repeated node identities.
    assert(solver.hasCycle(head) == expected);
    for (std::size_t i = 0; i < storage.size(); ++i) {
        assert(storage[i]->next == originalNext[i]);
        assert(storage[i]->val == 7);
    }
}

int main() {
    int checked = 0;
    for (int length = 0; length <= 8; ++length) {
        for (int entry = -1; entry < length; ++entry) {
            checkStructure(length, entry);
            ++checked;
        }
    }
    assert(checked == 45);
    checkStructure(9999, -1);  // Odd acyclic tail.
    checkStructure(10000, -1); // Even acyclic tail.
    checkStructure(10000, 9000); // Long prefix, shorter cycle.
    checkStructure(10000, 1000); // Shorter prefix, long cycle.
    checkStructure(10000, 0); // Whole chain is a cycle.
    checkStructure(10000, 9999); // Last node loops to itself.
    std::cout << "Cycle detection: 45 structures agree with identity-set oracle; input unchanged; 6 long structures passed\n";
}
