#include <functional>
#include <tuple>

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
 * You are given the root of a binary tree. We install cameras on the tree nodes where each camera
 * at a node can monitor its parent, itself, and its immediate children.
 *
 * Return the minimum number of cameras needed to monitor all nodes of the tree.
 *
 * ! The number of nodes in the tree is in the range [1, 1000].
 * ! Node.val == 0
 */

class Solution {
public:
    int minCameraCover(TreeNode* root)
    {
        return approach2(root);
    }

private:
    enum State { NotCovered, Covered_HasCamera, Covered_NoCamera };

    int approach2(TreeNode* root)
    {
        int result = 0;
        std::function<State(TreeNode*)> dfs = [&](TreeNode* root) {
            if (!root)
                return State::Covered_NoCamera;

            const auto left = dfs(root->left);
            const auto right = dfs(root->right);
            if (left == NotCovered || right == NotCovered) {
                result++;
                return Covered_HasCamera;
            }
            if (left == Covered_HasCamera || right == Covered_HasCamera)
                return Covered_NoCamera;

            return NotCovered;
        };
        if (dfs(root) == NotCovered) {
            result++;
        }
        return result;
    }

    int approach1(TreeNode* root)
    {
        // return[0] = min num of cameras that current node has a camera and it is covered by itself
        // return[1] = min num of cameras that current node has no camera and it is covered by its
        // parent return[2] = min num of cameras that current node has no camera and it is covered
        // by one of its children
        std::function<std::tuple<int, int, int>(TreeNode*)> dfs = [&](TreeNode* root) {
            if (!root)
                return std::make_tuple(INT_MAX / 2, 0, 0);

            const auto [left0, left1, left2] = dfs(root->left);
            const auto [right0, right1, right2] = dfs(root->right);
            // case 1: current node has a camera
            const int case1 = 1 + std::min({left0, left1, left2}) + std::min({right0, right1, right2});
            // case 2: current node has no camera and it is covered by its parent
            // then its children must be covered by itself or covered by their children
            const int case2 = std::min(left0, left2) + std::min(right0, right2);
            // case 3: current node has no camera and it is covered by one of its children
            const int case3 = std::min({left0 + right0, left0 + right2, left2 + right0});
            return std::make_tuple(case1, case2, case3);
        };
        const auto [coveredBySelf, coveredByParent, coveredByChildren] = dfs(root);
        return std::min(coveredBySelf, coveredByChildren);
    }
};
