#include <queue>
#include <vector>

/**
 * You have some number of sticks with positive integer lengths. These lengths are given as an array
 * sticks, where sticks[i] is the length of the ith stick.
 *
 * You can connect any two sticks of lengths x and y into one stick by paying a cost of x + y. You
 * must connect all the sticks until there is only one stick remaining.
 *
 * Return the minimum cost of connecting all the given sticks into one stick in this way.
 *
 * ! 1 <= sticks.length <= 10^4
 * ! 1 <= sticks[i] <= 10^4
 */

class Solution {
public:
    int connectSticks(std::vector<int>& sticks)
    {
        std::priority_queue<int, std::vector<int>, std::greater<>> pq(sticks.begin(), sticks.end());
        int result = 0;
        while (pq.size() >= 2) {
            const int x = pq.top();
            pq.pop();
            const int y = pq.top();
            pq.pop();
            result += x + y;
            pq.push(x + y);
        }
        return result;
    }
};
