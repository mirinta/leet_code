#include <array>
#include <functional>
#include <string>
#include <vector>

/**
 * You are given a list of strings of the same length words and a string target.
 *
 * Your task is to form target using the given words under the following rules:
 *
 * - target should be formed from left to right.
 *
 * - To form the ith character (0-indexed) of target, you can choose the kth character of the jth
 * string in words if target[i] = words[j][k].
 *
 * - Once you use the kth character of the jth string of words, you can no longer use the xth
 * character of any string in words where x <= k. In other words, all characters to the left of or
 * at index k become unusuable for every string.
 *
 * - Repeat the process until you form the string target.
 *
 * Notice that you can use multiple characters from the same string in words provided the conditions
 * above are met.
 *
 * Return the number of ways to form target from words. Since the answer may be too large, return it
 * modulo 10^9 + 7.
 *
 * ! 1 <= words.length <= 1000
 * ! 1 <= words[i].length <= 1000
 * ! All strings in words have the same length.
 * ! 1 <= target.length <= 1000
 * ! words[i] and target contain only lowercase English letters.
 */

class Solution {
public:
    int numWays(std::vector<std::string>& words, std::string target)
    {
        return approach2(words, target);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(const std::vector<std::string>& words, const std::string& target)
    {
        const int m = target.size();
        const int n = words[0].size();
        // count[i][j] = num of words that the ith character of each word is character j
        std::vector<std::array<long long, 26>> count(n);
        for (const auto& w : words) {
            for (int i = 0; i < n; ++i) {
                count[i][w[i] - 'a']++;
            }
        }
        // dp[i][j] = num of ways to make up target[0:i-1] using the first j characters of words
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = 1;
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                const int case1 = dp[i][j - 1];
                const int case2 = dp[i - 1][j - 1] * count[j - 1][target[i - 1] - 'a'] % kMod;
                dp[i][j] = (case1 + case2) % kMod;
            }
        }
        return dp[m][n];
    }

    int approach1(const std::vector<std::string>& words, const std::string& target)
    {
        const int m = target.size();
        const int n = words[0].size();
        // count[i][j] = num of words that the ith character of each word is character j
        std::vector<std::array<long long, 26>> count(n);
        for (const auto& w : words) {
            for (int i = 0; i < n; ++i) {
                count[i][w[i] - 'a']++;
            }
        }
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        std::function<int(int, int)> dfs = [&](int i, int k) {
            if (i == target.size())
                return 1;

            if (k == count.size() || target.size() - i > count.size() - k)
                return 0;

            if (memo[i][k] != -1)
                return memo[i][k];

            const int case1 = dfs(i, k + 1);
            const int case2 = dfs(i + 1, k + 1) * count[k][target[i] - 'a'] % kMod;
            return memo[i][k] = (case1 + case2) % kMod;
        };
        return dfs(0, 0);
    }
};