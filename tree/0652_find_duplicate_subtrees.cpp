#include <string>
#include <unordered_map>
#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

/**
 * Given the root of a binary tree, return all duplicate subtrees.
 *
 * For each kind of duplicate subtrees, you only need to return the root node of any one of them.
 *
 * Two trees are duplicate if they have the same structure with the same node values.
 *
 * ! The number of the nodes in the tree will be in the range [1, 5000]
 * ! -200 <= Node.val <= 200
 */

class Solution {
public:
    std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root)
    {
        std::unordered_map<std::string, int> keys;
        std::vector<TreeNode*> result;
        dfs(result, keys, root);
        return result;
    }

private:
    std::string dfs(std::vector<TreeNode*>& result, std::unordered_map<std::string, int>& keys, TreeNode* root)
    {
        if (!root)
            return "#";

        auto s = std::to_string(root->val);
        s.push_back(',');
        s.append(dfs(result, keys, root->left));
        s.push_back(',');
        s.append(dfs(result, keys, root->right));
        if (keys[s]++ == 1) {
            result.push_back(root);
        }
        return s;
    }
};
