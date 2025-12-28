#include <numeric>
#include <vector>

/**
 * You are given "nums", an array of positive integers of size "2 * n". You must perform "n"
 * operations on this array.
 *
 * In the ith operation (1-indexed), you will:
 *
 * - Choose two elements, x and y.
 *
 * - Receive a score of i * gcd(x, y).
 *
 * - Remove x and y from nums.
 *
 * Return the maximum score you can receive after performing "n" operations.
 *
 * The function gcd(x, y) is the greatest common divisor of x and y.
 *
 * ! 1 <= n <= 7
 * ! nums.length == 2 * n
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    int maxScore(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::vector<int>> gcd(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                gcd[i][j] = std::gcd(nums[i], nums[j]);
                gcd[j][i] = gcd[i][j];
            }
        }
        std::vector<int> memo(1 << n, -1);
        return dfs(memo, 1, 0, nums.size(), gcd);
    }

private:
    int dfs(std::vector<int>& memo, int operation, int state, int n, const std::vector<std::vector<int>>& gcd)
    {
        if (state == (1 << n) - 1)
            return 0;

        if (memo[state] != -1)
            return memo[state];

        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            if ((state >> i) & 1)
                continue;

            for (int j = 0; j < n; ++j) {
                if (i == j || (state >> j) & 1)
                    continue;

                const int score = operation * gcd[i][j];
                result = std::max(result, score + dfs(memo, operation + 1, state | (1 << i) | (1 << j), n, gcd));
            }
        }
        return memo[state] = result;
    }
};