#include <queue>
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
 * Given the root of a binary tree, return the vertical order traversal of its nodes' values. (i.e.,
 * from top to bottom, column by column).
 *
 * If two nodes are in the same row and column, the order should be from left to right.
 *
 * ! The number of nodes in the tree is in the range [0, 100].
 * ! -100 <= Node.val <= 100
 */

class Solution {
public:
    std::vector<std::vector<int>> verticalOrder(TreeNode* root)
    {
        /**    (id)
         *     root
         *     /  \
         *  left  right
         * (id-1) (id+1)
         */
        if (!root)
            return {};

        int minID = INT_MAX;
        int maxID = INT_MIN;
        std::unordered_map<int, std::vector<int>> map; // id to nodes
        std::queue<std::pair<int, TreeNode*>> queue;   // <id, node>
        queue.emplace(0, root);
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                auto [id, node] = queue.front();
                queue.pop();
                minID = std::min(minID, id);
                maxID = std::max(maxID, id);
                map[id].push_back(node->val);
                if (node->left) {
                    queue.emplace(id - 1, node->left);
                }
                if (node->right) {
                    queue.emplace(id + 1, node->right);
                }
            }
        }
        std::vector<std::vector<int>> result;
        for (int id = minID; id <= maxID; ++id) {
            result.push_back(map[id]);
        }
        return result;
    }
};
