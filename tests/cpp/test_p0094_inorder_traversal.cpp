#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

std::vector<std::string> shapes(int count) {
    if (count == 0) return {"."};
    std::vector<std::string> result;
    for (int left = 0; left < count; ++left)
        for (const auto& first : shapes(left))
            for (const auto& second : shapes(count - 1 - left))
                result.push_back("N" + first + second);
    return result;
}

using Storage = std::vector<std::unique_ptr<TreeNode>>;
TreeNode* build(const std::string& shape, std::size_t& offset, Storage& storage) {
    assert(offset < shape.size());
    if (shape[offset++] == '.') return nullptr;
    storage.push_back(std::make_unique<TreeNode>(static_cast<int>(storage.size() % 7) - 3));
    TreeNode* node = storage.back().get();
    node->left = build(shape, offset, storage);
    node->right = build(shape, offset, storage);
    return node;
}

Storage chain(int count, bool left) {
    Storage storage;
    for (int i = 0; i < count; ++i) storage.push_back(std::make_unique<TreeNode>(i % 7 - 3));
    for (int i = 1; i < count; ++i) {
        if (left) storage[i-1]->left = storage[i].get();
        else storage[i-1]->right = storage[i].get();
    }
    return storage;
}

struct Snapshot { TreeNode* left; TreeNode* right; int value; };
std::vector<Snapshot> snapshot(const Storage& storage) {
    std::vector<Snapshot> result;
    for (const auto& node : storage) result.push_back({node->left, node->right, node->val});
    return result;
}

void unchanged(const Storage& storage, const std::vector<Snapshot>& before) {
    for (std::size_t i = 0; i < storage.size(); ++i) {
        assert(storage[i]->left == before[i].left);
        assert(storage[i]->right == before[i].right);
        assert(storage[i]->val == before[i].value);
    }
}

#include "../../cpp/p0094_inorder_traversal.cpp"

void recursiveOracle(TreeNode* root, std::vector<int>& result) {
    if (!root) return;
    recursiveOracle(root->left, result);
    result.push_back(root->val);
    recursiveOracle(root->right, result);
}
void check(TreeNode* root, const Storage& storage) {
    const auto before = snapshot(storage);
    std::vector<int> expected;
    recursiveOracle(root, expected);
    assert(Solution().inorderTraversal(root) == expected);
    unchanged(storage, before);
    auto mappedExpected = expected;
    for (int& value : mappedExpected) value = 2 * value + 1;
    for (const auto& node : storage) node->val = 2 * node->val + 1;
    const auto mappedBefore = snapshot(storage);
    assert(Solution().inorderTraversal(root) == mappedExpected);
    unchanged(storage, mappedBefore);
    for (std::size_t i = 0; i < storage.size(); ++i) storage[i]->val = before[i].value;
    unchanged(storage, before);
}

int main() {
    int checked = 0;
    for (int count = 0; count <= 6; ++count) {
        for (const auto& shape : shapes(count)) {
            Storage storage;
            std::size_t offset = 0;
            TreeNode* root = build(shape, offset, storage);
            assert(offset == shape.size() && storage.size() == static_cast<std::size_t>(count));
            check(root, storage);
            ++checked;
        }
    }
    assert(checked == 197);
    for (bool left : {false, true}) {
        auto storage = chain(100, left);
        check(storage.front().get(), storage);
    }
    std::cout << "197 tree shapes and two 100-node skew chains passed with topology and 199 value-mapping checks\n";
}
