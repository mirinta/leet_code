#include <string>
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
 * Given the root of a binary tree, return all root-to-leaf paths in any order.
 *
 * A leaf is a node with no children.
 *
 * ! The number of nodes in the tree is in the range [1, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    std::vector<std::string> binaryTreePaths(TreeNode* root)
    {
        std::vector<std::string> result;
        std::string path;
        dfs(result, path, root);
        return result;
    }

private:
    void dfs(std::vector<std::string>& result, std::string& path, TreeNode* root)
    {
        if (!root)
            return;

        if (!root->left && !root->right) {
            result.push_back(path);
            result.back().append(std::to_string(root->val));
            return;
        }
        const int len = path.size();
        path.append(std::to_string(root->val));
        path.append("->");
        dfs(result, path, root->left);
        dfs(result, path, root->right);
        path.erase(len);
    }
};
