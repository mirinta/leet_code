#include <unordered_map>
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
 * You are given a 2D integer array descriptions where descriptions[i] = [parenti, childi, isLefti]
 * indicates that parenti is the parent of childi in a binary tree of unique values. Furthermore,
 *
 * - If isLefti == 1, then childi is the left child of parenti.
 *
 * - If isLefti == 0, then childi is the right child of parenti.
 *
 * Construct the binary tree described by descriptions and return its root.
 *
 * The test cases will be generated such that the binary tree is valid.
 *
 * ! 1 <= descriptions.length <= 10^4
 * ! descriptions[i].length == 3
 * ! 1 <= parenti, childi <= 10^5
 * ! 0 <= isLefti <= 1
 * ! The binary tree described by descriptions is valid.
 */

class Solution {
public:
    TreeNode* createBinaryTree(std::vector<std::vector<int>>& descriptions)
    {
        std::unordered_map<int, std::pair<bool, TreeNode*>> map; // map[val] = <has_parent, node>
        for (const auto& desc : descriptions) {
            if (!map.count(desc[1])) {
                map[desc[1]] = {false, new TreeNode(desc[1])};
            }
            map[desc[1]].first = true;
            if (!map.count(desc[0])) {
                map[desc[0]] = {false, new TreeNode(desc[0])};
            }
            if (desc[2]) {
                map[desc[0]].second->left = map[desc[1]].second;
            } else {
                map[desc[0]].second->right = map[desc[1]].second;
            }
        }
        for (const auto& [val, info] : map) {
            if (!info.first)
                return info.second;
        }
        return nullptr;
    }
};
