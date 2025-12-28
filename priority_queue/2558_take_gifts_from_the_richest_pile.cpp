#include <cmath>
#include <queue>
#include <vector>

/**
 * You are given an integer array gifts denoting the number of gifts in various piles. Every second,
 * you do the following:
 *
 * - Choose the pile with the maximum number of gifts.
 *
 * - If there is more than one pile with the maximum number of gifts, choose any.
 *
 * - Leave behind the floor of the square root of the number of gifts in the pile. Take the rest of
 * the gifts.
 *
 * Return the number of gifts remaining after k seconds.
 *
 * ! 1 <= gifts.length <= 10^3
 * ! 1 <= gifts[i] <= 10^9
 * ! 1 <= k <= 10^3
 */

class Solution {
public:
    long long pickGifts(std::vector<int>& gifts, int k)
    {
        std::priority_queue<long long> pq(gifts.begin(), gifts.end());
        for (int i = 0; i < k; ++i) {
            if (pq.top() == 1)
                break;

            const auto top = pq.top();
            pq.pop();
            pq.push(std::sqrt(top));
        }
        long long result = 0;
        while (!pq.empty()) {
            result += pq.top();
            pq.pop();
        }
        return result;
    }
};