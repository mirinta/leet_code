#include <stack>
#include <vector>

/**
 * There are n people standing in a queue, and they numbered from 0 to n - 1 in left to right order. You are given an
 * array heights of distinct integers where heights[i] represents the height of the ith person.
 *
 * A person can see another person to their right in the queue if everybody in between is shorter than both of them.
 * More formally, the ith person can see the jth person if i < j and min(heights[i], heights[j]) > max(heights[i+1],
 * heights[i+2], ..., heights[j-1]).
 *
 * Return an array answer of length n where answer[i] is the number of people the ith person can see to their right in
 * the queue.
 *
 * ! n == heights.length
 * ! 1 <= n <= 10^5
 * ! 1 <= heights[i] <= 10^5
 * ! All the values of heights are unique.
 */

class Solution {
public:
    std::vector<int> canSeePersonsCount(std::vector<int>& heights)
    {
        const int n = heights.size();
        std::stack<int> stack;
        std::vector<int> result(n, 0);
        for (int i = n - 1; i >= 0; --i) {
            int count = 0;
            while (!stack.empty() && heights[i] >= stack.top()) {
                stack.pop();
                count++;
            }
            result[i] = count + !stack.empty();
            stack.push(heights[i]);
        }
        return result;
    }
};