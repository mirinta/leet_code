#include <queue>
#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * 给定一棵二叉树，设计一个算法，创建含有某一深度上所有节点的链表（比如，若一棵树的深度为
 * D，则会创建出 D 个链表）。返回一个包含所有深度的链表的数组。
 */

class Solution {
public:
    std::vector<ListNode*> listOfDepth(TreeNode* tree)
    {
        if (!tree)
            return {};

        std::queue<TreeNode*> queue;
        queue.push(tree);
        std::vector<ListNode*> result;
        while (!queue.empty()) {
            ListNode vHead(-1);
            auto* curr = &vHead;
            for (int k = queue.size(); k > 0; --k) {
                auto* node = queue.front();
                queue.pop();
                curr->next = new ListNode(node->val);
                curr = curr->next;
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
            }
            result.push_back(vHead.next);
        }
        return result;
    }
};