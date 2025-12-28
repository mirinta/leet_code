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
 * 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
 *
 * B是A的子结构， 即A中有出现和B相同的结构和节点值。
 *
 * ! 0 <= 节点个数 <= 10000
 */

class Solution {
public:
    bool isSubStructure(TreeNode* A, TreeNode* B)
    {
        if (!A || !B)
            return false;

        if (A->val == B->val && doesAHaveB(A, B))
            return true;

        return isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }

private:
    bool doesAHaveB(TreeNode* rootA, TreeNode* rootB)
    {
        if (!rootB)
            return true;

        if (!rootA)
            return false;

        if (rootA->val != rootB->val)
            return false;

        return doesAHaveB(rootA->left, rootB->left) && doesAHaveB(rootA->right, rootB->right);
    }
};