#include <numeric>
#include <unordered_map>
#include <vector>

/**
 * Given a 0-indexed integer array nums of length n and an integer k, return the number of pairs (i,
 * j) such that:
 *
 * - 0 <= i < j <= n - 1 and
 *
 * - nums[i] * nums[j] is divisible by k.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i], k <= 10^5
 */

class Solution {
public:
    long long countPairs(std::vector<int>& nums, int k)
    {
        // given nums[j], count the num of nums[i] where
        // i < j and nums[i] * nums[j] % k = 0
        // let x be a factor of nums[j] and k
        // then k/x must be the factor of nums[i]
        std::vector<int> divisors;
        for (int d = 1; d * d <= k; ++d) {
            if (k % d != 0)
                continue;

            divisors.push_back(d);
            if (d * d < k) {
                divisors.push_back(k / d);
            }
        }
        std::unordered_map<int, int> map;
        long long result = 0;
        for (const auto& val : nums) {
            result += map[k / std::gcd(val, k)];
            for (const auto& d : divisors) {
                if (val % d == 0) {
                    map[d]++;
                }
            }
        }
        return result;
    }
};