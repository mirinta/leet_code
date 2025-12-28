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
 * You are given an integer n. There is a complete binary tree with 2n - 1 nodes. The root of that
 * tree is the node with the value 1, and every node with a value val in the range [1, 2n - 1 - 1]
 * has two children where:
 *
 * - The left node has the value 2 * val, and
 *
 * - The right node has the value 2 * val + 1.
 *
 * You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each
 * query, solve the following problem:
 *
 * 1. Add an edge between the nodes with values ai and bi.
 *
 * 2. Find the length of the cycle in the graph.
 *
 * 3. Remove the added edge between nodes with values ai and bi.
 *
 * Note that:
 *
 * - A cycle is a path that starts and ends at the same node, and each edge in the path is visited
 * only once.
 *
 * - The length of a cycle is the number of edges visited in the cycle.
 *
 * - There could be multiple edges between two nodes in the tree after adding the edge of the query.
 *
 * Return an array answer of length m where answer[i] is the answer to the ith query.
 *
 * ! 2 <= n <= 30
 * ! m == queries.length
 * ! 1 <= m <= 10^5
 * ! queries[i].length == 2
 * ! 1 <= ai, bi <= 2^n - 1
 * ! ai != bi
 */

class Solution {
public:
    std::vector<int> cycleLengthQueries(int n, std::vector<std::vector<int>>& queries)
    {
        std::vector<int> result(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            // our goal is to find the LCA of p and q
            // - the parent node of node x is x/2
            // - if p is deeper than q, let p = p/2 (go to its parent node)
            // - if q is deeper than q, let q = q/2 (go to its parent node)
            // - if p = q, then we found the LCA
            int p = queries[i][0];
            int q = queries[i][1];
            int length = 0;
            while (p != q) {
                if (p > q) {
                    p /= 2;
                } else {
                    q /= 2;
                }
                length++;
            }
            result[i] = length + 1; // plus the added edge between p and q
        }
        return result;
    }
};
