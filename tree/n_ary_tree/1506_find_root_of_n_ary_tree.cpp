#include <unordered_set>
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
 * You are given all the nodes of an N-ary tree as an array of Node objects, where each node has a
 * unique value.
 *
 * Return the root of the N-ary tree.
 *
 * ! The total number of nodes is between [1, 5 * 10^4].
 * ! Each node has a unique value.
 *
 * ! Could you solve this problem in constant space complexity with a linear time algorithm?
 */

class Solution {
public:
    Node* findRoot(std::vector<Node*> tree)
    {
        return approach2(tree);
    }

private:
    // time O(N), space O(1)
    Node* approach2(const std::vector<Node*>& tree)
    {
        // all values are unique
        int sum = 0;
        for (auto* const node : tree) {
            sum += node->val;
            for (auto* const child : node->children) {
                sum -= child->val;
            }
        }
        for (auto* const node : tree) {
            if (node->val == sum)
                return node;
        }
        return nullptr;
    }

    // time O(N), space O(N)
    Node* approach1(const std::vector<Node*>& tree)
    {
        std::unordered_set<Node*> visited;
        for (auto* const node : tree) {
            for (auto* child : node->children) {
                visited.emplace(child);
            }
        }
        for (auto* const node : tree) {
            if (!visited.count(node))
                return node;
        }
        return nullptr;
    }
};