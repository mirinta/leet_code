#include <string>
#include <vector>

/**
 * Given an array of integers cost and an integer target, return the maximum integer you can paint
 * under the following rules:
 *
 * - The cost of painting a digit (i + 1) is given by cost[i] (0-indexed).
 *
 * - The total cost used must be equal to target.
 *
 * - The integer does not have 0 digits.
 *
 * Since the answer may be very large, return it as a string. If there is no way to paint any
 * integer given the condition, return "0".
 *
 * ! cost.length == 9
 * ! 1 <= cost[i], target <= 5000
 */

class Solution {
public:
    std::string largestNumber(std::vector<int>& cost, int target)
    {
        // dp[i] = max integer we can make such that the total cost is equal to i
        std::vector<std::string> dp(1 + target, "0");
        dp[0] = "";
        for (int i = 1; i <= target; ++i) {
            for (int d = 1; d <= 9; ++d) {
                if (i < cost[d - 1] || dp[i - cost[d - 1]] == "0")
                    continue;

                const auto s = dp[i - cost[d - 1]] + std::to_string(d);
                if (s.size() > dp[i].size() || (s.size() == dp[i].size() && s > dp[i])) {
                    dp[i] = s;
                }
            }
        }
        return dp[target];
    }
};