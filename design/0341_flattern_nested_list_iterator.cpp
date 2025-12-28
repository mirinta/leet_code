#include <vector>

/**
 * This is the interface that allows for creating nested lists.
 * You should not implement it, or speculate about its implementation
 */
class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const std::vector<NestedInteger>& getList() const;
};

/**
 * You are given a nested list of integers nestedList. Each element is either an integer or a list
 * whose elements may also be integers or other lists. Implement an iterator to flatten it.
 *
 * Implement the NestedIterator class:
 *
 * - NestedIterator(List<NestedInteger> nestedList) Initializes the iterator with the nested list
 * nestedList.
 *
 * - int next() Returns the next integer in the nested list.
 *
 * - boolean hasNext() Returns true if there are still some integers in the nested list and false
 * otherwise.
 *
 * Your code will be tested with the following pseudocode:
 *
 * initialize iterator with nestedList
 * res = []
 * while iterator.hasNext()
 *     append iterator.next() to the end of res
 * return res
 *
 * If res matches the expected flattened list, then your code will be judged as correct.
 *
 * ! 1 <= nestedList.length <= 500
 * ! The values of the integers in the nested list is in the range [-10^6, 10^6].
 */

class NestedIterator {
public:
    NestedIterator(std::vector<NestedInteger>& nestedList)
    {
        helper(nestedList);
    }

    int next()
    {
        if (hasNext())
            return data[idx++];

        return INT_MIN;
    }

    bool hasNext()
    {
        return idx < data.size();
    }

private:
    void helper(const std::vector<NestedInteger>& nestedList)
    {
        for (const auto& e : nestedList) {
            if (e.isInteger()) {
                data.push_back(e.getInteger());
            } else {
                helper(e.getList());
            }
        }
    }

private:
    size_t idx = 0;
    std::vector<int> data;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
