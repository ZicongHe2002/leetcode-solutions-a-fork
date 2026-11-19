#include <algorithm>
#include <queue>
// TreeNode is provided by the judge or test harness.
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;
        std::queue<TreeNode*> pending;
        pending.push(root);
        while (!pending.empty()) {
            TreeNode* node = pending.front();
            pending.pop();
            std::swap(node->left, node->right);
            if (node->left != nullptr) pending.push(node->left);
            if (node->right != nullptr) pending.push(node->right);
        }
        return root;
    }
};
