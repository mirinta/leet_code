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
 * 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回
 * false。假设输入的数组的任意两个数字都互不相同。
 *
 * ! 数组长度 <= 1000
 */

class Solution {
public:
    bool verifyPostorder(std::vector<int>& postorder)
    {
        if (postorder.size() <= 1)
            return true;

        return verify(0, postorder.size() - 1, postorder);
    }

private:
    bool verify(int start, int end, const std::vector<int>& postorder)
    {
        if (start >= end)
            return true;

        const auto& rootValue = postorder[end];
        // [start, left) are values in left subtree
        int left = start;
        while (left < end && postorder[left] < rootValue) {
            left++;
        }
        // expected: [left+1, end) are values in right subtree
        int right = left;
        while (right < end && postorder[right] > rootValue) {
            right++;
        }
        if (right != end)
            return false;

        return verify(start, left - 1, postorder) && verify(left, end - 1, postorder);
    }
};