#include <queue>
#include <unordered_map>
#include <unordered_set>

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
 * You are given the root of a binary tree with unique values, and an integer start. At minute 0, an
 * infection starts from the node with value start.
 *
 * Each minute, a node becomes infected if:
 *
 * - The node is currently uninfected.
 *
 * - The node is adjacent to an infected node.
 *
 * Return the number of minutes needed for the entire tree to be infected
 *
 * ! The number of nodes in the tree is in the range [1, 10^5].
 * ! 1 <= Node.val <= 10^5
 * ! Each node has a unique value.
 * ! A node with a value of start exists in the tree.
 */

class Solution {
public:
    int amountOfTime(TreeNode* root, int start)
    {
        std::unordered_map<int, std::pair<TreeNode*, TreeNode*>> map; // val to <node, parent>
        dfs(map, root, nullptr);
        std::queue<int> queue;
        queue.push(start);
        std::unordered_set<int> visited;
        visited.insert(start);
        int result = -1;
        while (!queue.empty()) {
            for (int s = queue.size(); s > 0; --s) {
                const auto val = queue.front();
                queue.pop();
                const auto& [curr, parent] = map[val];
                for (const auto* const node : {curr->left, curr->right, parent}) {
                    if (node && !visited.count(node->val)) {
                        queue.push(node->val);
                        visited.insert(node->val);
                    }
                }
            }
            result++;
        }
        return result;
    }

private:
    void dfs(std::unordered_map<int, std::pair<TreeNode*, TreeNode*>>& map, TreeNode* curr, TreeNode* parent)
    {
        if (!curr)
            return;

        map[curr->val] = {curr, parent};
        dfs(map, curr->left, curr);
        dfs(map, curr->right, curr);
    }
};