#include <unordered_map>
#include <vector>

/**
 * A frog is crossing a river. The river is divided into some number of units, and at each unit,
 * there may or may not exist a stone. The frog can jump on a stone, but it must not jump into the
 * water.
 *
 * Given a list of stones' positions (in units) in sorted ascending order, determine if the frog can
 * cross the river by landing on the last stone. Initially, the frog is on the first stone and
 * assumes the first jump must be 1 unit.
 *
 * If the frog's last jump was k units, its next jump must be either k - 1, k, or k + 1 units. The
 * frog can only jump in the forward direction.
 *
 * ! 2 <= stones.length <= 2000
 * ! 0 <= stones[i] <= 2^31 - 1
 * ! stones[0] == 0
 * ! stones is sorted in a strictly increasing order.
 */

class Solution {
public:
    bool canCross(std::vector<int>& stones)
    {
        const int n = stones.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[stones[i]] = i;
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dp(memo, 0, 0, stones, map);
    }

private:
    bool dp(std::vector<std::vector<int>>& memo,
            int i,
            int k,
            const std::vector<int>& stones,
            const std::unordered_map<int, int>& map)
    {
        if (i == stones.size() - 1)
            return true;

        if (memo[i][k] != -1)
            return memo[i][k];

        for (int dist = k - 1; dist <= k + 1; ++dist) {
            if (dist <= 0 || !map.count(stones[i] + dist))
                continue;

            if (dp(memo, map.at(stones[i] + dist), dist, stones, map))
                return memo[i][k] = 1;
        }
        return memo[i][k] = 0;
    }
};