#include <algorithm>
#include <utility>
#include <vector>
// TreeNode is provided by the judge or test harness.
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        std::vector<std::pair<TreeNode*, int>> pending{{root, 1}};
        int best = 0;
        while (!pending.empty()) {
            const auto entry = pending.back();
            pending.pop_back();
            TreeNode* node = entry.first;
            const int depth = entry.second;
            best = std::max(best, depth);
            if (node->left != nullptr) pending.emplace_back(node->left, depth + 1);
            if (node->right != nullptr) pending.emplace_back(node->right, depth + 1);
        }
        return best;
    }
};
