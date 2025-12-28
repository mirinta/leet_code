#include <array>
#include <unordered_map>
#include <vector>

/**
 * The chess knight has a unique movement, it may move two squares vertically and one square
 * horizontally, or two squares horizontally and one square vertically (with both forming the shape
 * of an L). The possible movements of chess knight are shown in this diagram:
 *
 * A chess knight can move as indicated in the chess diagram below:
 *
 * We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric
 * cell (i.e. blue cell).
 *
 * Given an integer n, return how many distinct phone numbers of length n we can dial.
 *
 * You are allowed to place the knight on any numeric cell initially and then you should perform n -
 * 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
 *
 * As the answer may be very large, return the answer modulo 10^9 + 7.
 *
 * ! 1 <= n <= 5000
 */

class Solution {
public:
    int knightDialer(int n)
    {
        return approach2(n);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    const std::unordered_map<int, std::vector<int>> map{{0, {4, 6}},    {1, {6, 8}}, {2, {7, 9}},    {3, {4, 8}},
                                                        {4, {0, 3, 9}}, {5, {}},     {6, {0, 1, 7}}, {7, {2, 6}},
                                                        {8, {1, 3}},    {9, {2, 4}}};

    // DP with space optimization, time O(N), space O(1)
    int approach2(int n)
    {
        std::array<int, 10> dp;
        dp.fill(1);
        auto prev = dp;
        for (int i = 2; i <= n; ++i) {
            prev = dp;
            dp.fill(0);
            for (int j = 0; j < 10; ++j) {
                for (const auto& k : map.at(j)) {
                    dp[j] = (dp[j] + prev[k]) % kMod;
                }
            }
        }
        int result = 0;
        for (const auto& val : dp) {
            result = (result + val) % kMod;
        }
        return result;
    }

    // DP, time O(N), space O(N)
    int approach1(int n)
    {
        // dp[i][j] = num of distinct phone numbers ending at value j after moving i steps
        std::vector<std::array<int, 10>> dp(1 + n, std::array<int, 10>{0});
        for (int j = 0; j < 10; ++j) {
            dp[1][j] = 1;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < 10; ++j) {
                for (const auto& k : map.at(j)) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][k]) % kMod;
                }
            }
        }
        int result = 0;
        for (const auto& val : dp[n]) {
            result = (result + val) % kMod;
        }
        return result;
    }
};