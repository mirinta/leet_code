#include <array>
#include <string>

/**
 * You are given a binary string s and a positive integer k.
 *
 * Return the length of the longest subsequence of s that makes up a binary number less than or
 * equal to k.
 *
 * Note:
 *
 * - The subsequence can contain leading zeroes.
 *
 * - The empty string is considered to be equal to 0.
 *
 * - A subsequence is a string that can be derived from another string by deleting some or no
 * characters without changing the order of the remaining characters.
 *
 * ! 1 <= s.length <= 1000
 * ! s[i] is either '0' or '1'.
 * ! 1 <= k <= 10^9
 */

class Solution
{
public:
    int longestSubsequence(std::string s, int k) { return dfs(0, s, k, binaryBits(k))[1]; }

private:
    int binaryBits(int val)
    {
        if (val == 0)
            return 1;

        int result = 0;
        while (val) {
            result++;
            val >>= 1;
        }
        return result;
    }

    // dfs[0] = value of the longest valid subsequence of s[0:n-1]
    // dfs[1] = length of dfs[0]
    std::array<int, 2> dfs(int i, const std::string& s, int k, int maxBits)
    {
        if (i == s.size())
            return {0, 0};

        auto [val, length] = dfs(i + 1, s, k, maxBits);
        if (s[i] == '0') {
            length++;
        } else if (length < maxBits && (1 << length) + val <= k) {
            val += (1 << length);
            length++;
        }
        return {val, length};
    }
};
