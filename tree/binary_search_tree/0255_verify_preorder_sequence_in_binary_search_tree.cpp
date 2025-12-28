#include <stack>
#include <vector>

/**
 * Given an array of unique integers preorder, return true if it is the correct preorder traversal
 * sequence of a binary search tree.
 *
 * ! 1 <= preorder.length <= 10^4
 * ! 1 <= preorder[i] <= 10^4
 * ! All the elements of preorder are unique.
 */

class Solution {
public:
    bool verifyPreorder(std::vector<int>& preorder)
    {
        return approach2(preorder);
    }

private:
    bool approach2(const std::vector<int>& preorder)
    {
        int min = INT_MIN;
        std::stack<int> stack;
        for (const auto& val : preorder) {
            while (!stack.empty() && val > stack.top()) {
                min = stack.top();
                stack.pop();
            }
            if (val <= min)
                return false;

            stack.push(val);
        }
        return true;
    }

    bool approach1(const std::vector<int>& preorder)
    {
        int i = 0;
        return dfs(preorder, i, INT_MIN, INT_MAX);
    }

    bool dfs(const std::vector<int>& preorder, int& i, int min, int max)
    {
        if (i == preorder.size())
            return true;

        const int root = preorder[i];
        if (root <= min || root >= max)
            return false;

        i++;
        return dfs(preorder, i, min, root) || dfs(preorder, i, root, max);
    }
};