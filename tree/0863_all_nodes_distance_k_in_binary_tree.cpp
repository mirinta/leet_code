#include <queue>
#include <unordered_map>
#include <unordered_set>
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
 * Given the root of a binary tree, the value of a target node target, and an integer k, return an
 * array of the values of all nodes that have a distance k from the target node.
 *
 * You can return the answer in any order.
 *
 * ! The number of nodes in the tree is in the range [1, 500].
 * ! 0 <= Node.val <= 500
 * ! All the values Node.val are unique.
 * ! target is the value of one of the nodes in the tree.
 * ! 0 <= k <= 1000
 */

class Solution {
public:
    // DFS + BFS: time O(N), space O(N), N is the number of nodes
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int k)
    {
        // all the values are unique,
        // so we can use node->val as vertex
        std::unordered_map<int, std::vector<int>> graph;
        buildGraph(graph, root);
        std::queue<int> queue;
        queue.push(target->val);
        std::unordered_set<int> visited;
        visited.insert(target->val);
        std::vector<int> result;
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int i = 0; i < size; ++i) {
                const auto v = queue.front();
                queue.pop();
                if (steps == k) {
                    result.push_back(v);
                }
                for (const auto& adj : graph[v]) {
                    if (!visited.count(adj)) {
                        visited.insert(adj);
                        queue.push(adj);
                    }
                }
            }
            steps++;
        }
        return result;
    }

private:
    void buildGraph(std::unordered_map<int, std::vector<int>>& graph, TreeNode* root)
    {
        if (!root)
            return;

        buildGraph(graph, root->left);
        buildGraph(graph, root->right);
        if (root->left) {
            graph[root->val].push_back(root->left->val);
            graph[root->left->val].push_back(root->val);
        }
        if (root->right) {
            graph[root->val].push_back(root->right->val);
            graph[root->right->val].push_back(root->val);
        }
    }
};
