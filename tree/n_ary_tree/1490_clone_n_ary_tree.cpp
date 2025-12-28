#include <vector>

/**
 * Definition for a Node.
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
 * Given a root of an N-ary tree, return a deep copy (clone) of the tree.
 *
 * Each node in the n-ary tree contains a val (int) and a list (List[Node]) of its children.
 *
 * class Node {
 *    public int val;
 *     public List<Node> children;
 * }
 *
 * Nary-Tree input serialization is represented in their level order traversal, each group of
 * children is separated by the null value (See examples).
 *
 * ! The depth of the n-ary tree is less than or equal to 1000.
 * ! The total number of nodes is between [0, 10^4].
 */

class Solution {
public:
    Node* cloneTree(Node* root)
    {
        if (!root)
            return nullptr;

        auto* clone = new Node(root->val);
        for (auto* child : root->children) {
            clone->children.push_back(cloneTree(child));
        }
        return clone;
    }
};