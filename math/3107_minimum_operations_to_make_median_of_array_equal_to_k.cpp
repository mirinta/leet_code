#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums and a non-negative integer k. In one operation, you can
 * increase or decrease any element by 1.
 *
 * Return the minimum number of operations needed to make the median of nums equal to k.
 *
 * The median of an array is defined as the middle element of the array when it is sorted in
 * non-decreasing order. If there are two choices for a median, the larger of the two values is
 * taken.
 *
 * ! 1 <= nums.length <= 2 * 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    long long minOperationsToMakeMedianK(std::vector<int>& nums, int k)
    {
        // 0 ... mid-1 mid mid+1 ... n-1
        // |<---part1--->| |<--part2-->|
        // mid = n/2
        // we want elements of part1 <= k
        // and elements of part2 >= k
        std::sort(nums.begin(), nums.end());
        const int n = nums.size();
        const int mid = n / 2;
        if (nums[mid] == k)
            return 0;

        long long result = 0;
        if (nums[mid] > k) {
            for (int i = n / 2; i >= 0; --i) {
                if (nums[i] <= k)
                    break;

                result += nums[i] - k;
            }
        } else {
            for (int i = n / 2; i < n; ++i) {
                if (nums[i] >= k)
                    break;

                result += k - nums[i];
            }
        }
        return result;
    }
};