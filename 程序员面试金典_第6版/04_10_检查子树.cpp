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
 * 检查子树。你有两棵非常大的二叉树：T1，有几万个节点；T2，有几万个节点。设计一个算法，判断 T2
 * 是否为 T1 的子树。
 *
 * 如果 T1 有这么一个节点 n，其子树与 T2 一模一样，则 T2 为 T1 的子树，也就是说，从节点 n
 * 处把树砍断，得到的树与 T2 完全相同。
 *
 * 注意：此题相对书上原题略有改动。
 *
 * ! 树的节点数目范围为[0, 20000]。
 */

class Solution {
public:
    bool checkSubTree(TreeNode* t1, TreeNode* t2)
    {
        if (!t1 && !t2)
            return true;

        if (!t1 || !t2)
            return false;

        if (dfs(t1, t2))
            return true;

        return checkSubTree(t1->left, t2) || checkSubTree(t1->right, t2);
    }

private:
    bool dfs(TreeNode* root1, TreeNode* root2)
    {
        if (!root1 && !root2)
            return true;

        if (!root1 || !root2 || root1->val != root2->val)
            return false;

        return dfs(root1->left, root2->left) && dfs(root1->right, root2->right);
    }
};