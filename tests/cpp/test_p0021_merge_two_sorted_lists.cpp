#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

// The online judge supplies this type; the solution file only uses it.
struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value = 0, ListNode* successor = nullptr)
        : val(value), next(successor) {}
};
#include "../../cpp/p0021_merge_two_sorted_lists.cpp"

struct OwnedList {
    std::vector<std::unique_ptr<ListNode>> storage;
    std::vector<ListNode*> nodes;
    explicit OwnedList(const std::vector<int>& values) {
        for (int value : values) {
            storage.push_back(std::make_unique<ListNode>(value));
            nodes.push_back(storage.back().get());
        }
        for (std::size_t i = 1; i < nodes.size(); ++i) nodes[i-1]->next = nodes[i];
    }
    ListNode* head() const { return nodes.empty() ? nullptr : nodes.front(); }
};

int main() {
    std::vector<std::vector<int>> cases;
    int combinations = 1;
    for (int length = 0; length <= 4; ++length) {
        for (int code = 0; code < combinations; ++code) {
            int value = code;
            std::vector<int> values(length);
            for (int& item : values) { item = value % 3 - 1; value /= 3; }
            if (std::is_sorted(values.begin(), values.end())) cases.push_back(values);
        }
        combinations *= 3;
    }
    assert(cases.size() == 35);
    int checked = 0;
    for (const auto& first : cases) {
        for (const auto& second : cases) {
            OwnedList a(first), b(second);
            auto expected = a.nodes;
            expected.insert(expected.end(), b.nodes.begin(), b.nodes.end());
            std::stable_sort(expected.begin(), expected.end(),
                             [](ListNode* x, ListNode* y) { return x->val < y->val; });
            ListNode* cursor = Solution{}.mergeTwoLists(a.head(), b.head());
            // Catches copied nodes, dropped duplicates, cycles, and unstable ties.
            for (ListNode* node : expected) {
                assert(cursor == node);
                cursor = cursor->next;
            }
            assert(cursor == nullptr);
            for (std::size_t i = 0; i < first.size(); ++i) assert(a.nodes[i]->val == first[i]);
            for (std::size_t i = 0; i < second.size(); ++i) assert(b.nodes[i]->val == second[i]);
            ++checked;
        }
    }
    assert(checked == 1225);
    // Each input reaches the problem's length bound; equal keys test tie order.
    OwnedList equalFirst(std::vector<int>(50, 7));
    OwnedList equalSecond(std::vector<int>(50, 7));
    auto expectedEqual = equalFirst.nodes;
    expectedEqual.insert(expectedEqual.end(), equalSecond.nodes.begin(), equalSecond.nodes.end());
    ListNode* cursor = Solution{}.mergeTwoLists(equalFirst.head(), equalSecond.head());
    for (ListNode* node : expectedEqual) {
        assert(cursor == node);
        assert(cursor->val == 7);
        cursor = cursor->next;
    }
    assert(cursor == nullptr);
    std::cout << "Merge lists: 1225 sorted-input pairs preserve exact nodes, values and stable order; 50+50 equal-key nodes preserve tie identity order\n";
}
