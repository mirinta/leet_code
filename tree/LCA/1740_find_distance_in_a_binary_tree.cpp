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
 * Given the root of a binary tree and two integers p and q, return the distance between the nodes
 * of value p and value q in the tree.
 *
 * The distance between two nodes is the number of edges on the path from one to the other.
 *
 * ! The number of nodes in the tree is in the range [1, 10^4].
 * ! 0 <= Node.val <= 10^9
 * ! All Node.val are unique.
 * ! p and q are values in the tree.
 */

class Solution {
public:
    int findDistance(TreeNode* root, int p, int q)
    {
        // dist(p, q) = dist(p, LCA) + dist(q, LCA)
        // dist(p, LCA) = dist(p, root) - dist(LCA, root)
        // dist(q, LCA) = dist(q, root) - dist(LCA, root)
        // thus, dist(p, q) = dist(p, root) + dist(q, root) - 2 * dist(LCA, root)
        if (p == q)
            return 0;

        int distP = -1;
        int distQ = -1;
        int distLCA = -1;
        dfs(distP, distQ, distLCA, root, p, q, 0);
        return distP + distQ - 2 * distLCA;
    }

private:
    int dfs(int& distP, int& distQ, int& distLCA, TreeNode* root, int p, int q, int dist)
    {
        if (!root)
            return 0;

        int count = 0;
        if (root->val == p) {
            distP = dist;
            count++;
        } else if (root->val == q) {
            distQ = dist;
            count++;
        }
        count += dfs(distP, distQ, distLCA, root->left, p, q, dist + 1);
        count += dfs(distP, distQ, distLCA, root->right, p, q, dist + 1);
        if (count == 2 && distLCA == -1) {
            distLCA = dist;
        }
        return count;
    }
};