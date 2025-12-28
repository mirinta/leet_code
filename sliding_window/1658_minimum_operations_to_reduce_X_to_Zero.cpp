#include <numeric>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and an integer x. In one operation, you can either remove the
 * leftmost or the rightmost element from the array nums and subtract its value from x. Note that
 * this modifies the array for future operations.
 *
 * Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise,
 * return -1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^4
 * ! 1 <= x <= 10^9
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums, int x)
    {
        // 0 ... x-1 x ... y y+1 ... n-1
        // |<--A-->| |<-B->| |<---C--->|
        // let A = sum of nums[0:x-1], B = sum of nums[x:y], C = sum of nums[y+1:n-1]
        // if we can reduce x to 0 by removing nums[0:x-1] and nums[y+1:n-1],
        // then A+B = x
        // since A+B+C = total_sum, then C = total_sum - x
        // to minimize nums[0:x-1].length + nums[y+1:n-1].length,
        // it is equal to N - max length of nums[x:y] such that sum of its elements is C
        const int n = nums.size();
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        if (total < x)
            return -1;

        const int target = total - x;
        int sum = 0;
        int maxL = INT_MIN;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum > target) {
                sum -= nums[left++];
            }
            if (sum == target) {
                maxL = std::max(maxL, right - left + 1);
            }
        }
        return maxL == INT_MIN ? -1 : n - maxL;
    }
};