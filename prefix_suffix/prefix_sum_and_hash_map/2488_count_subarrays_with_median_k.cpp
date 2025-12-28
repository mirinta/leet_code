#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of size n consisting of distinct integers from 1 to n and a positive
 * integer k.
 *
 * Return the number of non-empty subarrays in nums that have a median equal to k.
 *
 * Note:
 *
 * - The median of an array is the middle element after sorting the array in ascending order. If the
 * array is of even length, the median is the left middle element. For example, the median of
 * [2,3,1,4] is 2, and the median of [8,4,3,5,1] is 4.
 *
 * - A subarray is a contiguous part of an array.
 *
 *  ! n == nums.length
 *  !1 <= n <= 10^5
 *  !1 <= nums[i], k <= n
 *  !The integers in nums are distinct.
 */

class Solution {
public:
    int countSubarrays(std::vector<int>& nums, int k)
    {
        // sum[i] = sum of nums[0:i]
        // - if nums[i] > k, sum += 1
        // - if nums[i] < k, sum -=1
        // - otherwise, sum += 0
        //
        // k is the median of an subarray:
        // - if the subarray has odd length, then sum of the subarray = 0
        // - if the subarray has even length, the sum of the subarray = 1
        //
        // given sum[i]
        // - if map[sum[i]] = j, then sum[i] - sum[j] = 0
        //   it means the sum of nums[j+1:i] = 0, length = i-j must be odd
        // - if map[sum[i]-1] = j, then sum[i] - sum[j] = 1
        //   it means the sum of nums[j+1:i] = 1, length = i-j must be even
        const int n = nums.size();
        std::unordered_map<int, int> mapOdd; // mapOdd[sum[j]] = freq and j is odd
        mapOdd[0] = 1;
        std::unordered_map<int, int> mapEven; // mapEven[sum[j]] = freq and j is even
        int sum = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i] > k ? 1 : (nums[i] < k ? -1 : 0);
            if (i & 1) {
                result += mapEven[sum];    // i-j is odd, i is odd, j is even
                result += mapOdd[sum - 1]; // i-j is even, i is odd, j is odd
                mapOdd[sum]++;
            } else {
                result += mapOdd[sum];      // i-j is odd, i is even, j is odd
                result += mapEven[sum - 1]; // i-j is even, i is even, j is even
                mapEven[sum]++;
            }
        }
        return result;
    }
};