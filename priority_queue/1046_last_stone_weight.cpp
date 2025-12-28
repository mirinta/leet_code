#include <queue>
#include <vector>

/**
 * You are given an array of integers "stones" where "stones[i]" is the weight of the "i"th stone.
 *
 * We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash
 * them together. Suppose the heaviest two stones have weights "w" and "y" with "x <= y". The
 * result of this smash is:
 *
 * - If x == y, both stones are destroyed, and
 *
 * - If x != y, the stone of weight "x" is destroyed, and the stone of weight "y" has new weight "y
 * - x".
 *
 * At the end of the game, there is at most one stone left.
 *
 * Return the weight of the last remaining stones. If there are no stones left, return "0".
 */

class Solution {
public:
    int lastStoneWeight(std::vector<int>& stones)
    {
        if (stones.empty())
            return 0;

        if (stones.size() == 1)
            return stones.front();

        std::priority_queue<int, std::vector<int>> pq;
        for (const auto& weight : stones) {
            pq.push(weight);
        }
        while (pq.size() > 1) {
            const auto weight1 = pq.top();
            pq.pop();
            const auto weight2 = pq.top();
            pq.pop();
            if (weight1 != weight2) {
                pq.push(weight1 - weight2);
            }
        }
        return pq.empty() ? 0 : pq.top();
    }
};
