#include <vector>

/**
 * Definition for a Node.
 *
 */
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val)
    {
        val = _val;
        left = nullptr;
        right = nullptr;
    }

    Node(int _val, Node* _left, Node* _right)
    {
        val = _val;
        left = _left;
        right = _right;
    }
};

/**
 * 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
 *
 * ! 本题与LC 426相同。
 */

class Solution {
public:
    Node* treeToDoublyList(Node* root)
    {
        if (!root)
            return nullptr;

        auto* leftHead = treeToDoublyList(root->left);
        auto* rightHead = treeToDoublyList(root->right);
        Node* leftTail = nullptr;
        Node* rightTail = nullptr;
        if (leftHead) {
            leftTail = leftHead->left;
            root->left = leftTail;
            leftTail->right = root;
        } else {
            leftHead = root;
            leftTail = root;
        }
        if (rightHead) {
            rightTail = rightHead->left;
            root->right = rightHead;
            rightHead->left = root;
        } else {
            rightHead = root;
            rightTail = root;
        }
        leftHead->left = rightTail;
        rightTail->right = leftHead;
        return leftHead;
    }
};
