#include <queue>
#include <unordered_map>
#include <unordered_set>

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
 * You have a binary tree with a small defect. There is exactly one invalid node where its right
 * child incorrectly points to another node at the same depth but to the invalid node's right.
 *
 * Given the root of the binary tree with this defect, root, return the root of the binary tree
 * after removing this invalid node and every node underneath it (minus the node it incorrectly
 * points to).
 *
 * Custom testing:
 *
 * The test input is read as 3 lines:
 *
 * - TreeNode root
 *
 * - int fromNode (not available to correctBinaryTree)
 *
 * - int toNode (not available to correctBinaryTree)
 *
 * After the binary tree rooted at root is parsed, the TreeNode with value of fromNode will have its
 * right child pointer pointing to the TreeNode with a value of toNode. Then, root is passed to
 * correctBinaryTree.
 *
 *
 * ! The number of nodes in the tree is in the range [3, 10^4].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! fromNode != toNode
 * ! fromNode and toNode will exist in the tree and will be on the same depth.
 * ! toNode is to the right of fromNode.
 * ! fromNode.right is null in the initial tree from the test data.
 */

class Solution {
public:
    TreeNode* correctBinaryTree(TreeNode* root)
    {
        if (!root)
            return nullptr;

        TreeNode* invalidNode = nullptr;
        std::queue<TreeNode*> queue;
        queue.push(root);
        std::unordered_set<TreeNode*> set;
        std::unordered_map<TreeNode*, TreeNode*> map; // child to parent
        while (!queue.empty()) {
            set.clear();
            for (int i = queue.size(); i > 0; --i) {
                set.insert(queue.front());
                queue.pop();
            }
            for (auto* node : set) {
                if (node->right && set.count(node->right)) {
                    invalidNode = node;
                    break;
                }
                if (node->left) {
                    queue.push(node->left);
                    map[node->left] = node;
                }
                if (node->right) {
                    queue.push(node->right);
                    map[node->right] = node;
                }
            }
            if (invalidNode)
                break;
        }
        if (!invalidNode)
            return root;

        auto* parent = map[invalidNode];
        parent->left = parent->left == invalidNode ? nullptr : parent->left;
        parent->right = parent->right == invalidNode ? nullptr : parent->right;
        return root;
    }
};