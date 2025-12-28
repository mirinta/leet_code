#include <vector>

/**
 * You are given an integer array nums of length n and a positive integer k.
 *
 * The power of an array of integers is defined as the number of subsequences with their sum equal
 * to k.
 *
 * Return the sum of power of all subsequences of nums.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n <= 100
 * ! 1 <= nums[i] <= 10^4
 * ! 1 <= k <= 100
 */

class Solution {
public:
    int sumOfPower(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(const std::vector<int>& nums, int k)
    {
        // dp[i][j] = sum of power of all subsequences of nums[0:i-1] with sum equal to j
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = 2 * dp[i - 1][j] % kMod;
                if (j >= nums[i - 1]) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - nums[i - 1]]) % kMod;
                }
            }
        }
        return dp[n][k];
    }

    int approach1(const std::vector<int>& nums, int k)
    {
        // dp[i][j] = num of subsequences of nums[0:i-1] ending at nums[i-1] with sum equal to j
        const int n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                const int diff = j - nums[i - 1];
                if (diff < 0)
                    continue;

                for (int x = i - 1; x >= 0; --x) {
                    dp[i][j] = (dp[i][j] + fastPowMod(2, i - x - 1, kMod) * dp[x][diff] % kMod) % kMod;
                }
            }
        }
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            result = (result + dp[i][k] * fastPowMod(2, n - i, kMod) % kMod) % kMod;
        }
        return result;
    }

    long long fastPowMod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};