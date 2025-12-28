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
 * Given a n-ary tree, find its maximum depth.
 *
 * The maximum depth is the number of nodes along the longest path from the root node down to the
 * farthest leaf node.
 *
 * Nary-Tree input serialization is represented in their level order traversal, each group of
 * children is separated by the null value (See examples).
 *
 * ! The total number of nodes is in the range [0, 10^4].
 * ! The depth of the n-ary tree is less than or equal to 1000.
 */

class Solution {
public:
    int maxDepth(Node* root)
    {
        return approach2(root);
    }

private:
    // BFS, TC = O(N), SC = O(N)
    int approach2(Node* root)
    {
        if (!root)
            return 0;

        std::queue<Node*> queue;
        queue.push(root);
        int result = 0;
        while (!queue.empty()) {
            for (int i = queue.size(); i > 0; --i) {
                auto* node = queue.front();
                queue.pop();
                for (auto* child : node->children) {
                    if (child) {
                        queue.push(child);
                    }
                }
            }
            result++;
        }
        return result;
    }

    // DFS, TC = O(N), SC = O(N)
    int approach1(Node* root)
    {
        if (!root)
            return 0;

        int result = 0;
        for (auto* child : root->children) {
            result = std::max(result, approach1(child));
        }
        return result + 1;
    }
};