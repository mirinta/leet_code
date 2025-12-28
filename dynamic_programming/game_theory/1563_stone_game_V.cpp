#include <vector>

/**
 * There are several stones arranged in a row, and each stone has an associated value which is an
 * integer given in the array stoneValue.
 *
 * In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right
 * row), then Bob calculates the value of each row which is the sum of the values of all the stones
 * in this row. Bob throws away the row which has the maximum value, and Alice's score increases by
 * the value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide
 * which row will be thrown away. The next round starts with the remaining row.
 *
 * The game ends when there is only one stone remaining. Alice's is initially zero.
 *
 * Return the maximum score that Alice can obtain.
 *
 * ! 1 <= stoneValue.length <= 500
 * ! 1 <= stoneValue[i] <= 10^6
 */

class Solution {
public:
    int stoneGameV(std::vector<int>& stoneValue)
    {
        const int n = stoneValue.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + stoneValue[i - 1];
        }
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dp(memo, 0, n - 1, presum);
    }

private:
    // max score that Alice finally gets in the game nums[lo:hi]
    int dp(std::vector<std::vector<int>>& memo, int lo, int hi, const std::vector<int>& presum)
    {
        if (hi <= lo)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        // choose a partition index x
        // lo ..... x x+1 .... hi
        // |<-left->| |<-right->|
        int result = 0;
        for (int x = lo; x < hi; ++x) {
            const int left = presum[x + 1] - presum[lo];
            const int right = presum[hi + 1] - presum[x + 1];
            int score = 0;
            if (left > right) {
                score = right + dp(memo, x + 1, hi, presum);
            } else if (left < right) {
                score = left + dp(memo, lo, x, presum);
            } else {
                const int case1 = right + dp(memo, x + 1, hi, presum);
                const int case2 = left + dp(memo, lo, x, presum);
                score = std::max(case1, case2);
            }
            result = std::max(result, score);
        }
        return memo[lo][hi] = result;
    }
};