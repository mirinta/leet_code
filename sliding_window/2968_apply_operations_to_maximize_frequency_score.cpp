#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer k.
 *
 * You can perform the following operation on the array at most k times:
 *
 * Choose any index i from the array and increase or decrease nums[i] by 1.
 * The score of the final array is the frequency of the most frequent element in the array.
 *
 * Return the maximum score you can achieve.
 *
 * The frequency of an element is the number of occurrences of that element in the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= k <= 10^14
 */

class Solution {
public:
    int maxFrequencyScore(std::vector<int>& nums, long long k)
    {
        // median theorem
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::vector<long long> presum(n + 1, 0); // presum[i] = sum of nums[0:i-1]
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (helper(left, right, presum) > k) {
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

private:
    // return the minimum num of operations
    // to make all elements of nums[j:i] equal
    // #operations = |nums[j]-x| + |nums[j+1]-x| + ... + |nums[i]-x|
    // to minimize #operations, let x = median of nums[j:i]
    long long helper(int left, int right, const std::vector<long long>& presum)
    {
        const int mid = left + (right - left) / 2;
        const long long median = presum[mid + 1] - presum[mid];
        const long long area1 = median * (mid - left) - (presum[mid] - presum[left]);
        const long long area2 = (presum[right + 1] - presum[mid + 1]) - median * (right - mid);
        return area1 + area2;
    }
};