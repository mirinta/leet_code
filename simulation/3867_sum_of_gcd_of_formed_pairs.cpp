#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given an integer array nums of length n.
 *
 * Construct an array prefixGcd where for each index i:
 *
 * - Let mxi = max(nums[0], nums[1], ..., nums[i]).
 *
 * - prefixGcd[i] = gcd(nums[i], mxi).
 *
 * After constructing prefixGcd:
 *
 * Sort prefixGcd in non-decreasing order.
 *
 * - Form pairs by taking the smallest unpaired element and the largest unpaired element.
 *
 * - Repeat this process until no more pairs can be formed.
 *
 * - For each formed pair, compute the gcd of the two elements.
 *
 * - If n is odd, the middle element in the prefixGcd array remains unpaired and should be ignored.
 *
 * Return an integer denoting the sum of the GCD values of all formed pairs.
 *
 * The term gcd(a, b) denotes the greatest common divisor of a and b.
 *
 * ! 1 <= n == nums.length <= 10^5
 * ! 1 <= nums[i] <= 10​​​​​​​^9
 */

class Solution {
public:
    long long gcdSum(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<long long> prefixGcd(n);
        for (int i = 0, max = 0; i < n; ++i) {
            max = std::max(max, nums[i]);
            prefixGcd[i] = std::gcd(nums[i], max);
        }
        std::sort(prefixGcd.begin(), prefixGcd.end());
        long long result = 0;
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            result += std::gcd(prefixGcd[i], prefixGcd[j]);
        }
        return result;
    }
};