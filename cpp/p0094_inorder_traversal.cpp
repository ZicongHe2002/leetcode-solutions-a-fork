#include <vector>
// TreeNode is provided by the judge or test harness.
class Solution {
public:
    std::vector<int> inorderTraversal(TreeNode* root) {
        std::vector<int> result;
        std::vector<TreeNode*> pending;
        TreeNode* current = root;
        while (current != nullptr || !pending.empty()) {
            while (current != nullptr) {
                pending.push_back(current);
                current = current->left;
            }
            current = pending.back();
            pending.pop_back();
            result.push_back(current->val);
            current = current->right;
        }
        return result;
    }
};
