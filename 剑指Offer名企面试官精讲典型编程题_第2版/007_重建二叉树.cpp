#include <unordered_map>
#include <vector>

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * 输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。
 *
 * 假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
 *
 * ! 本题与LC 105相同。
 */

class Solution {
public:
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
    {
        if (preorder.size() != inorder.size() || preorder.empty())
            return nullptr;

        map.clear();
        for (int i = 0; i < inorder.size(); ++i) {
            map[inorder[i]] = i;
        }
        return build(0, preorder.size() - 1, 0, inorder.size() - 1, preorder, inorder);
    }

private:
    std::unordered_map<int, int> map; // node value to node index in inorder vector

    TreeNode* build(int preStart,
                    int preEnd,
                    int inStart,
                    int inEnd,
                    const std::vector<int>& preorder,
                    const std::vector<int>& inorder)
    {
        if (preStart > preEnd || inStart > inEnd)
            return nullptr;

        const int rootValue = preorder[preStart];
        const int rootIndex = map[rootValue];
        const int numOfNodesInLeftSubTree = rootIndex - inStart;

        auto* root = new TreeNode(rootValue);
        root->left = build(preStart + 1, preStart + numOfNodesInLeftSubTree, inStart, rootIndex - 1, preorder, inorder);
        root->right = build(preStart + numOfNodesInLeftSubTree + 1, preEnd, rootIndex + 1, inEnd, preorder, inorder);
        return root;
    }
};