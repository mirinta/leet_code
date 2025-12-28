#include <stack>
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
 * Given the root of an n-ary tree, return the postorder traversal of its nodes' values.
 *
 * Nary-Tree input serialization is represented in their level order traversal. Each group of
 * children is separated by the null value (See examples)
 *
 * ! The number of nodes in the tree is in the range [0, 10^4].
 * ! 0 <= Node.val <= 10^4
 * ! The height of the n-ary tree is less than or equal to 1000.
 */

class Solution {
public:
    std::vector<int> postorder(Node* root)
    {
        return approach2(root);
    }

private:
    std::vector<int> approach2(Node* root)
    {
        if (!root)
            return {};

        std::stack<Node*> stack;
        stack.push(root);
        std::vector<int> result;
        while (!stack.empty()) {
            auto* node = stack.top();
            stack.pop();
            result.push_back(node->val);
            for (auto* child : node->children) {
                if (child) {
                    stack.push(child);
                }
            }
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::vector<int> approach1(Node* root)
    {
        std::vector<int> result;
        dfs(result, root);
        return result;
    }

    void dfs(std::vector<int>& result, Node* root)
    {
        if (!root)
            return;

        for (auto* child : root->children) {
            if (child) {
                dfs(result, child);
            }
        }
        result.push_back(root->val);
    }
};