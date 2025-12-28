#include <vector>

/**
 * This is the interface that allows for creating nested lists.
 * You should not implement it, or speculate about its implementation
 */
class NestedInteger {
public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger& ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const std::vector<NestedInteger>& getList() const;
};

/**
 * You are given a nested list of integers nestedList. Each element is either an integer or a list
 * whose elements may also be integers or other lists.
 *
 * The depth of an integer is the number of lists that it is inside of. For example, the nested list
 * [1,[2,2],[[3],2],1] has each integer's value set to its depth.
 *
 * Return the sum of each integer in nestedList multiplied by its depth.
 *
 * ! 1 <= nestedList.length <= 50
 * ! The values of the integers in the nested list is in the range [-100, 100].
 * ! The maximum depth of any integer is less than or equal to 50.
 */

class Solution {
public:
    int depthSum(std::vector<NestedInteger>& nestedList)
    {
        int result = 0;
        for (const auto& nested : nestedList) {
            result += dfs(nested, 1);
        }
        return result;
    }

private:
    int dfs(const NestedInteger& nested, int depth)
    {
        if (nested.isInteger())
            return nested.getInteger() * depth;

        int result = 0;
        for (const auto& child : nested.getList()) {
            result += dfs(child, depth + 1);
        }
        return result;
    }
};