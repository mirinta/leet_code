#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given the array nums consisting of n positive integers. You computed the sum of all
 * non-empty continuous subarrays from the array and then sorted them in non-decreasing order,
 * creating a new array of n * (n + 1) / 2 numbers.
 *
 * Return the sum of the numbers from index left to index right (indexed from 1), inclusive, in the
 * new array. Since the answer can be a huge number return it modulo 109 + 7.
 *
 * ! n == nums.length
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 100
 * ! 1 <= left <= right <= n * (n + 1) / 2
 */

class Solution {
public:
    int rangeSum(std::vector<int>& nums, int n, int left, int right)
    {
        return approach2(nums, n, left, right);
    }

private:
    static constexpr long long kMod = 1e9 + 7;

    // binary seach + sliding window
    int approach2(const std::vector<int>& nums, int n, int left, int right)
    {
        return (helper(right, nums) - helper(left - 1, nums) + kMod) % kMod;
    }

    // sum of the first k subarray sums
    long long helper(int k, const std::vector<int>& nums)
    {
        long long lo = *std::min_element(nums.begin(), nums.end());
        long long hi = std::accumulate(nums.begin(), nums.end(), 0LL);
        while (lo < hi) {
            const long long mid = lo + (hi - lo) / 2;
            if (countSubarrays(mid, nums).first >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        const auto [count, totalSum] = countSubarrays(lo, nums);
        return totalSum - lo * (count - k);
    }

    // return[0] = num of subarrays where the sum of elements <= target
    // return[1] = total sum of these valid subarrays
    std::pair<long long, long long> countSubarrays(long long target, const std::vector<int>& nums)
    {
        long long totalSum = 0;
        long long subarraysSum = 0;
        long long count = 0;
        for (int left = 0, right = 0, windowSum = 0; right < nums.size(); ++right) {
            windowSum += nums[right];
            // there are right-left+1 subarrays ending with nums[right] within nums[left:right]
            // nums[right] appears right-left+1 times in these subarrays
            subarraysSum += nums[right] * (right - left + 1);
            while (windowSum > target) {
                subarraysSum -= windowSum;
                windowSum -= nums[left];
                left++;
            }
            count += right - left + 1;
            totalSum += subarraysSum;
        }
        return {count, totalSum};
    }

    // brute-force
    int approach1(const std::vector<int>& nums, int n, int left, int right)
    {
        std::vector<long long> presum(n + 1);
        for (int i = 1; i <= n; ++i) {
            presum[i] = (presum[i - 1] + nums[i - 1]) % kMod;
        }
        std::vector<long long> subarraySums;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                subarraySums.push_back((presum[j + 1] - presum[i] + kMod) % kMod);
            }
        }
        std::sort(subarraySums.begin(), subarraySums.end());
        long long result = 0;
        for (int i = left - 1; i < right; ++i) {
            result = (result + subarraySums[i]) % kMod;
        }
        return result;
    }
};