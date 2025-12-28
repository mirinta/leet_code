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
 * We run a preorder depth-first search (DFS) on the root of a binary tree.
 *
 * At each node in this traversal, we output D dashes (where D is the depth of this node), then we
 * output the value of this node.  If the depth of a node is D, the depth of its immediate child is
 * D + 1. The depth of the root node is 0.
 *
 * If a node has only one child, that child is guaranteed to be the left child.
 *
 * Given the output traversal of this traversal, recover the tree and return its root.
 *
 * ! The number of nodes in the original tree is in the range [1, 1000].
 * ! 1 <= Node.val <= 10^9
 */

class Solution {
public:
    TreeNode* recoverFromPreorder(std::string traversal)
    {
        const int n = traversal.size();
        std::vector<std::pair<int, int>> nodes; // <value, depth>
        for (int i = 0; i < n; ++i) {
            int j = i;
            while (j < n && traversal[j] == '-') {
                j++;
            }
            const int depth = j - i;
            int value = 0;
            while (j < n && std::isdigit(traversal[j])) {
                value = value * 10 + (traversal[j] - '0');
                j++;
            }
            nodes.emplace_back(value, depth);
            i = j - 1;
        }
        int count = 0;
        return dfs(count, 0, nodes);
    }

private:
    TreeNode* dfs(int& count, int i, const std::vector<std::pair<int, int>>& nodes)
    {
        auto* root = new TreeNode(nodes[i].first);
        int leftCount = 0;
        if (i + 1 < nodes.size() && nodes[i].second + 1 == nodes[i + 1].second) {
            root->left = dfs(leftCount, i + 1, nodes);
        }
        int rightCount = 0;
        if (i + 1 + leftCount < nodes.size() && nodes[i].second + 1 == nodes[i + 1 + leftCount].second) {
            root->right = dfs(rightCount, i + 1 + leftCount, nodes);
        }
        count += 1 + leftCount + rightCount;
        return root;
    }
};
