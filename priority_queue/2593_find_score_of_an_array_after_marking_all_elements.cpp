#include <queue>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * Starting with score = 0, apply the following algorithm:
 *
 * - Choose the smallest integer of the array that is not marked. If there is a tie, choose the one
 * with the smallest index.
 *
 * - Add the value of the chosen integer to score.
 *
 * - Mark the chosen element and its two adjacent elements if they exist.
 *
 * - Repeat until all the array elements are marked.
 *
 * Return the score you get after applying the above algorithm.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    long long findScore(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::priority_queue<Pair, std::vector<Pair>, Compare> pq;
        for (int i = 0; i < n; ++i) {
            pq.emplace(nums[i], i);
        }
        std::vector<bool> marked(n, false);
        long long result = 0;
        while (!pq.empty()) {
            const auto [val, index] = pq.top();
            pq.pop();
            if (marked[index])
                continue;

            result += val;
            marked[index] = true;
            if (index - 1 >= 0 && !marked[index - 1]) {
                marked[index - 1] = true;
            }
            if (index + 1 < n && !marked[index + 1]) {
                marked[index + 1] = true;
            }
        }
        return result;
    }

private:
    using Pair = std::pair<long long, int>;

    struct Compare {
        bool operator()(const Pair& p1, const Pair& p2) const
        {
            if (p1.first == p2.first)
                return p1.second > p2.second;

            return p1.first > p2.first;
        }
    };
};