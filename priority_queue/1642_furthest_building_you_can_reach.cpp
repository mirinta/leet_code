#include <queue>
#include <vector>

/**
 * You are given an integer array heights representing the heights of buildings, some bricks, and
 * some ladders.
 *
 * You start your journey from building 0 and move to the next building by possibly using bricks or
 * ladders.
 *
 * While moving from building i to building i+1 (0-indexed),
 *
 * - If the current building's height is greater than or equal to the next building's height, you do
 * not need a ladder or bricks.
 *
 * - If the current building's height is less than the next building's height, you can either use
 * one ladder or (h[i+1] - h[i]) bricks.
 *
 * Return the furthest building index (0-indexed) you can reach if you use the given ladders and
 * bricks optimally.
 *
 * ! 1 <= heights.length <= 10^5
 * ! 1 <= heights[i] <= 10^6
 * ! 0 <= bricks <= 10^9
 * ! 0 <= ladders <= heights.length
 */

class Solution {
public:
    int furthestBuilding(std::vector<int>& heights, int bricks, int ladders)
    {
        const int n = heights.size();
        std::priority_queue<int, std::vector<int>, std::greater<>> pq; // min heap
        for (int i = 0; i + 1 < n; ++i) {
            const int diff = heights[i + 1] - heights[i];
            if (diff <= 0)
                continue;

            pq.push(diff);
            // case 1: use ladder first
            if (ladders > 0) {
                ladders--;
                continue;
            }
            // case 2: find the previous min diff, replace that ladder with bricks
            // then we can move from heights[i] to heights[i+1] using that ladder
            if (bricks < pq.top())
                return i;

            bricks -= pq.top();
            pq.pop();
        }
        return n - 1;
    }
};
