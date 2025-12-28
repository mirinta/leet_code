/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};

/**
 * Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
 *
 * Each node will have a reference to its parent node. The definition for Node is below:
 *
 * According to the definition of LCA on Wikipedia: "The lowest common ancestor of two nodes p and q
 * in a tree T is the lowest node that has both p and q as descendants (where we allow a node to be
 * a descendant of itself)."
 *
 * ! The number of nodes in the tree is in the range [2, 10^5].
 * ! -10^9 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p != q
 * ! p and q exist in the tree.
 */

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node* q)
    {
        if (!p || !q)
            return nullptr;

        // it is guaranteed that both p and q exist in the tree
        // all Node.val are unique
        // the problem is equivalent to finding the intersection of two linked lists
        auto* iterP = p;
        auto* iterQ = q;
        while (iterP != iterQ) {
            iterP = iterP ? iterP->parent : q;
            iterQ = iterQ ? iterQ->parent : p;
        }
        return iterP;
    }
};