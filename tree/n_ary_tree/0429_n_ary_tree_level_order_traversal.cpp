#include <queue>
#include <vector>

/**
 * Definition for a Node.
 */
class Node {
public:
    int val;
    std::vector<Node*> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, std::vector<Node*> _children)
    {
        val = _val;
        children = _children;
    }
};

/**
 * Given an n-ary tree, return the level order traversal of its nodes' values.
 *
 * Nary-Tree input serialization is represented in their level order traversal, each group of
 * children is separated by the null value (See examples).
 *
 * ! The height of the n-ary tree is less than or equal to 1000
 * ! The total number of nodes is between [0, 10^4]
 */

class Solution {
public:
    std::vector<std::vector<int>> levelOrder(Node* root)
    {
        if (!root)
            return {};

        std::vector<std::vector<int>> result;
        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            std::vector<int> values(queue.size(), 0);
            for (auto& val : values) {
                auto* node = queue.front();
                val = node->val;
                queue.pop();
                for (auto* child : node->children) {
                    if (child) {
                        queue.push(child);
                    }
                }
            }
            result.push_back(std::move(values));
        }
        return result;
    }
};