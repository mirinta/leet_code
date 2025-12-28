#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums of length n, and a positive integer k.
 *
 * The power of a subsequence is defined as the minimum absolute difference between any two elements
 * in the subsequence.
 *
 * Return the sum of powers of all subsequences of nums which have length equal to k.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * ! 2 <= n == nums.length <= 50
 * ! -10^8 <= nums[i] <= 10^8
 * ! 2 <= k <= n
 */

class Solution {
public:
    int sumOfPowers(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        long long result = 0;
        for (int a = 0; a < n; ++a) {
            for (int b = a + 1; b < n; ++b) {
                const int diff = nums[b] - nums[a];
                result = (result + helper(nums, k, a, b) * diff % kMod) % kMod;
            }
        }
        return result;
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // return the num of subsequences which have length equal to k
    // and nums[b]-nums[a] is the power of each subsequence
    // nums[a] and nums[b] must be included
    long long helper(const std::vector<int>& nums, int k, int a, int b)
    {
        const int n = nums.size();
        const int diff = nums[b] - nums[a];
        // [X X X X X a] X X X [b X X X X]
        // dp1[i][j] = num of subsequences of nums[0:i] ending at nums[i],
        // length is equal to j and power > diff, where i <= a and j <= k-1
        std::vector<std::vector<long long>> dp1(n, std::vector<long long>(k));
        for (int i = 0; i <= a; ++i) {
            dp1[i][1] = 1;
            for (int j = 2; j < k; ++j) {
                for (int t = 0; t < i && nums[i] - nums[t] > diff; ++t) {
                    dp1[i][j] = (dp1[i][j] + dp1[t][j - 1]) % kMod;
                }
            }
        }
        // dp2[i][j] = num of subsequences of nums[n-1:i] ending at nums[i],
        // length is equal to j and power >= diff, where i >= b and j <= k-1
        std::vector<std::vector<long long>> dp2(n, std::vector<long long>(k));
        for (int i = n - 1; i >= b; --i) {
            dp2[i][1] = 1;
            for (int j = 2; j < k; ++j) {
                for (int t = n - 1; t > i && nums[t] - nums[i] >= diff; --t) {
                    dp2[i][j] = (dp2[i][j] + dp2[t][j - 1]) % kMod;
                }
            }
        }
        long long count = 0;
        for (int t = 1; t <= k - 1; ++t) {
            count = (count + dp1[a][t] * dp2[b][k - t] % kMod) % kMod;
        }
        return count;
    }
};