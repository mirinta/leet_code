#include <queue>
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
 * Given the root of a binary search tree, a target value, and an integer k, return the k values in
 * the BST that are closest to the target. You may return the answer in any order.
 *
 * You are guaranteed to have only one unique set of k values in the BST that are closest to the
 * target.
 *
 * ! The number of nodes in the tree is n.
 * ! 1 <= k <= n <= 10^4.
 * ! 0 <= Node.val <= 10^9
 * ! -10^9 <= target <= 10^9
 */

class Solution {
public:
    std::vector<int> closestKValues(TreeNode* root, double target, int k)
    {
        return approach2(root, target, k);
    }

private:
    // inorder traversal + sliding window with deque, time O(N), space O(N+K)
    std::vector<int> approach2(TreeNode* root, double target, int k)
    {
        if (!root)
            return {};

        std::deque<int> deque;
        inorder(deque, root, target, k);
        std::vector<int> result;
        while (!deque.empty()) {
            result.push_back(deque.front());
            deque.pop_front();
        }
        return result;
    }

    void inorder(std::deque<int>& deque, TreeNode* root, double target, int k)
    {
        if (!root)
            return;

        inorder(deque, root->left, target, k);
        deque.push_back(root->val);
        if (deque.size() > k) {
            if (std::abs(deque.front() - target) < std::abs(deque.back() - target)) {
                deque.pop_back();
                // IMPORTANT! values are traversed in ascending order
                // if current value is farther from target,
                // it is not necessary to check the following values
                return;
            }
            deque.pop_front();
        }
        inorder(deque, root->right, target, k);
    }

    struct Comparator {
        explicit Comparator(double target) : target(target) {}

        bool operator()(const int v1, const int v2) const
        {
            return std::abs(v1 - target) < std::abs(v2 - target);
        };

        const double target{0};
    };

    // priority queue, time O(Nlogk), space O(N+k)
    std::vector<int> approach1(TreeNode* root, double target, int k)
    {
        if (!root)
            return {};

        std::priority_queue<int, std::vector<int>, Comparator> pq(Comparator{target}); // max heap
        preorder(pq, root, k);
        std::vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }

    void preorder(std::priority_queue<int, std::vector<int>, Comparator>& pq, TreeNode* root, int k)
    {
        if (!root)
            return;

        pq.emplace(root->val);
        if (pq.size() > k) {
            pq.pop();
        } // any kind of traversal is ok
        preorder(pq, root->left, k);
        preorder(pq, root->right, k);
    }
};