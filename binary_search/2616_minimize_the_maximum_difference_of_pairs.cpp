#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer p. Find p pairs of indices of nums
 * such that the maximum difference amongst all the pairs is minimized. Also, ensure no index
 * appears more than once amongst the p pairs.
 *
 * Note that for a pair of elements at the index i and j, the difference of this pair is |nums[i] -
 * nums[j]|, where |x| represents the absolute value of x.
 *
 * Return the minimum maximum difference among all p pairs. We define the maximum of an empty set to
 * be zero.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 * ! 0 <= p <= (nums.length)/2
 */

class Solution {
public:
    int minimizeMax(std::vector<int>& nums, int p)
    {
        std::sort(nums.begin(), nums.end());
        int lo = 0;
        int hi = nums.back() - nums.front();
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, p)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    // check if the max num of pairs >= p where the difference of each pair <= max
    bool isValid(int max, const std::vector<int>& nums, int p)
    {
        const int n = nums.size();
        int count = 0;
        int i = 0;
        while (i < n - 1) {
            if (nums[i + 1] - nums[i] <= max) {
                count++;
                i += 2;
            } else {
                i++;
            }
        }
        return count >= p;
    }
};