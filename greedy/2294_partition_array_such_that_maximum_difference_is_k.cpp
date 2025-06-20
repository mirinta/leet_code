#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums and an integer k. You may partition nums into one or more
 * subsequences such that each element in nums appears in exactly one of the subsequences.
 *
 * Return the minimum number of subsequences needed such that the difference between the maximum and
 * minimum values in each subsequence is at most k.
 *
 * A subsequence is a sequence that can be derived from another sequence by deleting some or no
 * elements without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 * ! 0 <= k <= 10^5
 */

class Solution
{
public:
    int partitionArray(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int i = 0;
        int result = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && nums[j] - nums[i] <= k) {
                j++;
            }
            result++;
            i = j;
        }
        return result;
    }
};
