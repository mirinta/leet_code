#include <algorithm>
#include <vector>

/**
 * The frequency of an element is the number of times it occurs in an array.
 *
 * You are given an integer array nums and an integer k. In one operation, you can choose an index
 * of nums and increment the element at that index by 1.
 *
 * Return the maximum possible frequency of an element after performing at most k operations.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    int maxFrequency(std::vector<int>& nums, int k)
    {
        // we can only increase an element
        // the greedy strategy to make nums[j:i] contain the same element
        // as much as possible is to increase all elements to its max element
        // if nums[j:i] is sorted in ascending order,
        // then num of operations = (nums[i]-nums[j])+...+(nums[i]-nums[i])
        // = (j-i+1)nums[i] - sum of nums[j:i] <= k
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        long long sum = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while ((long long)(right - left + 1) * nums[right] - sum > k) {
                sum -= nums[left];
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};