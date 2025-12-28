#include <string>
#include <unordered_set>
#include <vector>

/**
 * The variance of a string is defined as the largest difference between the number of occurrences
 * of any 2 characters present in the string. Note the two characters may or may not be the same.
 *
 * Given a string s consisting of lowercase English letters only, return the largest variance
 * possible among all substrings of s.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int largestVariance(std::string s)
    {
        // Largest variance = max(frequency(x) - frequency(y))
        // - x != y, x and y are characters represent in string s
        // - #NOTE# variance >= 0
        // Given a string and a character pair x and y,
        // the string can be written as: x x y y ? ? x y
        // Now, we want the frequency of x and y
        // - let x = 1, y = -1, and ? = 0
        // - the string can be written as: 1 1 -1 -1 0 0 1 -1
        // The problem is finding the maximum subarray sum in this string
        // - #NOTE#, the sum must contain at least one -1 and one 1
        std::unordered_set<char> set(s.begin(), s.end());
        int result = 0;
        // Enumerate all character pairs: x and y
        for (const char& x : set) {
            for (const char& y : set) {
                if (x == y)
                    continue;

                // Let x = 1, y = -1, and other characters = 0
                // DP with space optimization:
                // dp0 = max subarray sum that ends with nums[i], and it doesn't contain -1
                // dp1 = max subarray sum that ends with nums[i], and it contains -1
                int dp0 = 0;
                int dp1 = INT_MIN;
                for (int i = 0; i < s.size(); ++i) {
                    if (s[i] == x) {
                        dp0 = dp0 + 1;
                        dp1 = dp1 + 1;
                    } else if (s[i] == y) {
                        dp1 = std::max(dp0, dp1) - 1;
                        dp0 = 0;
                    }
                    result = std::max(result, dp1);
                }
            }
        }
        return result;
    }
};

// 2D DP: TLE
// dp[i][0] = max subarray sum that ends with the ith element, and it doesn't contain -1
// dp[i][1] = max subarray sum that ends with the ith element, and it contains -1
// std::vector<std::vector<int>> dp(1 + s.size(), std::vector<int>(2, 0));
// dp[0][0] = 0;
// dp[0][1] = INT_MIN;
// for (int i = 1; i <= s.size(); ++i) {
//     if (s[i - 1] == x) {
//         dp[i][0] = dp[i - 1][0] + 1;
//         dp[i][1] = dp[i - 1][1] + 1;
//     } else if (s[i - 1] == y) {
//         dp[i][0] = 0;
//         dp[i][1] = std::max(dp[i - 1][0], dp[i - 1][1]) - 1;
//     } else {
//         dp[i][0] = dp[i - 1][0];
//         dp[i][1] = dp[i - 1][1];
//     }
//     result = std::max(result, dp[i][1]);
// }