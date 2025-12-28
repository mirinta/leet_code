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
 * Given a root of an N-ary tree, you need to compute the length of the diameter of the tree.
 *
 * The diameter of an N-ary tree is the length of the longest path between any two nodes in the
 * tree. This path may or may not pass through the root.
 *
 * (Nary-Tree input serialization is represented in their level order traversal, each group of
 * children is separated by the null value.)
 *
 * ! The depth of the n-ary tree is less than or equal to 1000.
 * ! The total number of nodes is between [1, 10^4].
 */

class Solution {
public:
    int diameter(Node* root)
    {
        int result = 0;
        dfs(result, root);
        return result;
    }

private:
    // return the length of the longest path from root to its leaves
    // length = num of edges
    int dfs(int& result, Node* root)
    {
        if (!root)
            return 0;

        int longest = 0;
        int secondLongest = 0;
        for (auto* child : root->children) {
            const auto length = dfs(result, child) + 1;
            if (length > longest) {
                secondLongest = longest;
                longest = length;
            } else if (length > secondLongest) {
                secondLongest = length;
            }
        }
        result = std::max(result, longest + secondLongest);
        return longest;
    }
};