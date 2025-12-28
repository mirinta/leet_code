#include <queue>
#include <vector>

/**
 * Design an algorithm to encode an N-ary tree into a binary tree and decode the binary tree to get
 * the original N-ary tree. An N-ary tree is a rooted tree in which each node has no more than N
 * children. Similarly, a binary tree is a rooted tree in which each node has no more than 2
 * children. There is no restriction on how your encode/decode algorithm should work. You just need
 * to ensure that an N-ary tree can be encoded to a binary tree and this binary tree can be decoded
 * to the original N-nary tree structure.
 *
 * Nary-Tree input serialization is represented in their level order traversal, each group of
 * children is separated by the null value (See following example).
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! 0 <= Node.val <= 10^4
 * ! The height of the n-ary tree is less than or equal to 1000
 * ! Do not use class member/global/static variables to store states. Your encode and decode
 * ! algorithms should be stateless.
 */

/*
Definition for a Node.
*/
class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, std::vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root)
    {
        if (!root)
            return nullptr;

        /**
         *      parent          parent
         *     /  |  \     =>    /
         *    c0  c1  c2        c0
         *                       \
         *                        c1
         *                         \
         *                          c2
         */
        auto* result = new TreeNode(root->val);
        std::queue<std::pair<TreeNode*, Node*>> queue;
        queue.emplace(result, root);
        while (!queue.empty()) {
            auto [bNode, nNode] = queue.front();
            queue.pop();
            TreeNode dummy(-1);
            auto* node = &dummy;
            for (auto* child : nNode->children) {
                node->right = new TreeNode(child->val);
                queue.emplace(node->right, child);
                node = node->right;
            }
            bNode->left = dummy.right;
        }
        return result;
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root)
    {
        if (!root)
            return nullptr;

        auto* result = new Node(root->val);
        std::queue<std::pair<TreeNode*, Node*>> queue;
        queue.emplace(root, result);
        while (!queue.empty()) {
            auto [bNode, nNode] = queue.front();
            queue.pop();
            auto* child = bNode->left;
            while (child) {
                nNode->children.push_back(new Node(child->val));
                queue.emplace(child, nNode->children.back());
                child = child->right;
            }
        }
        return result;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
