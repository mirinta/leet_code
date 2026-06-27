#include <functional>
#include <unordered_map>

/**
 * Definition for a Node.
 */
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* random;
    Node() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
    Node(int x, Node* left, Node* right, Node* random) : val(x), left(left), right(right), random(random) {}
};

struct NodeCopy {
    int val;
    NodeCopy* left;
    NodeCopy* right;
    NodeCopy* random;
    NodeCopy() : val(0), left(nullptr), right(nullptr), random(nullptr) {}
    NodeCopy(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
    NodeCopy(int x, NodeCopy* left, NodeCopy* right, NodeCopy* random)
        : val(x), left(left), right(right), random(random)
    {
    }
};

/**
 * A binary tree is given such that each node contains an additional random pointer which could point to any node in the
 * tree or null.
 *
 * Return a deep copy of the tree.
 *
 * The tree is represented in the same input/output way as normal binary trees where each node is represented as a pair
 * of [val, random_index] where:
 *
 * - val: an integer representing Node.val
 *
 * - random_index: the index of the node (int the input) where the random pointer points to, or null if it does not
 * point to any node.
 *
 * You will be given the tree in class Node and you should return the cloned tree in class NodeCopy. NodeCopy class is
 * just a clone of Node class with the same attributes and constructors.
 *
 * ! The number of nodes in the tree is in the range [0, 1000].
 * ! 1 <= Node.val <= 10^6
 */

class Solution {
public:
    NodeCopy* copyRandomBinaryTree(Node* root)
    {
        std::unordered_map<Node*, NodeCopy*> map;
        std::function<NodeCopy*(Node*)> dfs = [&](Node* node) -> NodeCopy* {
            if (!node)
                return nullptr;

            if (map.count(node))
                return map[node];

            auto* copy = new NodeCopy(node->val);
            map[node] = copy;
            copy->left = dfs(node->left);
            copy->right = dfs(node->right);
            copy->random = dfs(node->random);
            return copy;
        };
        return dfs(root);
    }
};
