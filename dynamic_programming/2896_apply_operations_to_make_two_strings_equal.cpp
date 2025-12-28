#include <array>
#include <string>
#include <vector>

/**
 * You are given two 0-indexed binary strings s1 and s2, both of length n, and a positive integer x.
 *
 * You can perform any of the following operations on the string s1 any number of times:
 *
 * - Choose two indices i and j, and flip both s1[i] and s1[j]. The cost of this operation is x.
 *
 * - Choose an index i such that i < n - 1 and flip both s1[i] and s1[i + 1]. The cost of this
 * operation is 1.
 *
 * Return the minimum cost needed to make the strings s1 and s2 equal, or return -1 if it is
 * impossible.
 *
 * Note that flipping a character means changing it from 0 to 1 or vice-versa.
 *
 * ! n == s1.length == s2.length
 * ! 1 <= n, x <= 500
 * ! s1 and s2 consist only of the characters '0' and '1'.
 */

class Solution {
public:
    int minOperations(std::string s1, std::string s2, int x)
    {
        const int n = s1.size();
        int diff = 0;
        for (int i = 0; i < n; ++i) {
            if (s1[i] != s2[i]) {
                diff++;
            }
        }
        if (diff % 2 != 0)
            return -1;

        memo.resize(n, std::vector<std::array<int, 2>>(n + 1, {-1, -1}));
        return dp(0, 0, false, s1, s2, x);
    }

private:
    std::vector<std::vector<std::array<int, 2>>> memo;

    int dp(int i, int count, bool flippedByOperation2, const std::string& s1, const std::string& s2, int x)
    {
        const int n = s1.size();
        if (i == n)
            return 0;

        if ((flippedByOperation2 ^ s1[i]) == s2[i])
            return dp(i + 1, count, false, s1, s2, x);

        if (memo[i][count][flippedByOperation2] != -1)
            return memo[i][count][flippedByOperation2];

        const int case1 = x + dp(i + 1, count + 1, false, s1, s2, x);
        const int case2 = 1 + dp(i + 1, count, true, s1, s2, x);
        int result = std::min(case1, case2);
        if (count > 0) {
            result = std::min(result, dp(i + 1, count - 1, false, s1, s2, x));
        }
        return memo[i][count][flippedByOperation2] = result;
    }
};