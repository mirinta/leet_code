#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given a list of blocks, where blocks[i] = t means that the i-th block needs t units of
 * time to be built. A block can only be built by exactly one worker.
 *
 * A worker can either split into two workers (number of workers increases by one) or build a block
 * then go home. Both decisions cost some time.
 *
 * The time cost of spliting one worker into two workers is given as an integer split. Note that if
 * two workers split at the same time, they split in parallel so the cost would be split.
 *
 * Output the minimum time needed to build all blocks.
 *
 * Initially, there is only one worker.
 *
 * ! 1 <= blocks.length <= 1000
 * ! 1 <= blocks[i] <= 10^5
 * ! 1 <= split <= 100
 */

class Solution {
public:
    int minBuildTime(std::vector<int>& blocks, int split)
    {
        return approach2(blocks, split);
    }

private:
    // PQ, time O(NlogN), space O(N)
    int approach2(const std::vector<int>& blocks, int split)
    {
        // blocks = [1, 2, 3], split = 1
        // - min cost = 1 + max(3, 1 + max(1, 2))
        // blocks = [1, 2, 3, 4], split = 1
        // - min cost = 1 + max(4, 1 + max(3, 1 + max(1, 2)))
        //                                    |<---val1-->|
        //                         |<--------val2-------->|
        std::priority_queue<int, std::vector<int>, std::greater<>> pq; // min heap
        for (const auto& cost : blocks) {
            pq.push(cost);
        }
        while (pq.size() > 1) {
            const auto v1 = pq.top();
            pq.pop();
            const auto v2 = pq.top();
            pq.pop();
            pq.push(split + std::max(v1, v2));
        }
        return pq.top();
    }

    // top-down DP, time O(N^2), space O(N^2)
    int approach1(std::vector<int>& blocks, int split)
    {
        const int n = blocks.size();
        // always build the block with the highest cost first,
        // so we sort the "blocks" in descending order
        std::sort(blocks.begin(), blocks.end(), std::greater<int>());
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dp(memo, 0, 1, split, blocks);
    }

    // min cost of building blocks[i:n-1] with j workers
    int dp(std::vector<std::vector<int>>& memo, int i, int j, int split, const std::vector<int>& blocks)
    {
        if (i == blocks.size())
            return 0;

        if (j == 0)
            return INT_MAX / 2; // not enough workers

        if (j >= blocks.size() - i)
            return blocks[i]; // enough workers, no need to split

        if (memo[i][j] != -1)
            return memo[i][j];

        const int case1 = split + dp(memo, i, 2 * j, split,
                                     blocks); // only split, all workers split at the same time
        const int case2 = std::max(blocks[i], dp(memo, i + 1, j - 1, split, blocks)); // build block[i]
        memo[i][j] = std::min(case1, case2);
        return memo[i][j];
    }
};
