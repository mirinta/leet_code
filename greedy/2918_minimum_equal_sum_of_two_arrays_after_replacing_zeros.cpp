#include <vector>

/**
 * You are given two arrays nums1 and nums2 consisting of positive integers.
 *
 * You have to replace all the 0's in both arrays with strictly positive integers such that the sum
 * of elements of both arrays becomes equal.
 *
 * Return the minimum equal sum you can obtain, or -1 if it is impossible.
 *
 * ! 1 <= nums1.length, nums2.length <= 10^5
 * ! 0 <= nums1[i], nums2[i] <= 10^6
 */

class Solution {
public:
    long long minSum(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const auto [lowerBound1, upperBound1] = getBounds(nums1);
        const auto [lowerBound2, upperBound2] = getBounds(nums2);
        if (lowerBound1 > upperBound2 || lowerBound2 > upperBound1)
            return -1;

        return std::max(lowerBound1, lowerBound2);
    }

private:
    std::pair<long long, long long> getBounds(const std::vector<int>& nums)
    {
        int countZeros = 0;
        long long sum = 0;
        for (const auto& val : nums) {
            if (val == 0) {
                countZeros++;
            }
            sum += val;
        }
        if (countZeros == 0)
            return {sum, sum};

        return {sum + countZeros, LLONG_MAX};
    }
};