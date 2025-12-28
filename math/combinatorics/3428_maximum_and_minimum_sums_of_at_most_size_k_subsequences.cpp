#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums and a positive integer k. Return the sum of the maximum and
 * minimum elements of all subsequences of nums with at most k elements.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 1 <= k <= min(70, nums.length)
 */

class Solution {
public:
    int minMaxSums(std::vector<int>& nums, int k)
    {
        static constexpr long long kMod = 1e9 + 7;
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<long long>> comb(n + 1, std::vector<long long>(k + 1));
        for (int i = 0; i <= n; ++i) {
            comb[i][0] = 1;
        }
        for (int i = 0; i <= std::min(n, k); ++i) {
            comb[i][i] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % kMod;
            }
        }
        // presum[i][j] = comb[i][0] + ... + comb[i][j]
        std::vector<std::vector<long long>> presum(n + 1, std::vector<long long>(k + 1));
        for (int i = 0; i <= n; ++i) {
            presum[i][0] = comb[i][0];
            for (int j = 1; j <= k; ++j) {
                presum[i][j] = (presum[i][j - 1] + comb[i][j]) % kMod;
            }
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            // fix nums[i] as the max element
            // num of subsequnces = C(i,0) + C(i,1) + ... + C(i,k-1)
            result = (result + presum[i][std::min(i, k - 1)] * nums[i] % kMod) % kMod;
            // fix nums[i] as the min element
            // num of subsequnces = C(n-i-1,0) + C(n-i-1,1) + ... + C(n-i-1,k-1)
            result = (result + presum[n - i - 1][std::min(n - i - 1, k - 1)] * nums[i] % kMod) % kMod;
        }
        return result;
    }
};
