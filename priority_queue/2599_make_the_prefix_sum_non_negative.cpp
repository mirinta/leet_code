#include <queue>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. You can apply the following operation any number of
 * times:
 *
 * - Pick any element from nums and put it at the end of nums.
 *
 * The prefix sum array of nums is an array prefix of the same length as nums such that prefix[i] is
 * the sum of all the integers nums[j] where j is in the inclusive range [0, i].
 *
 * Return the minimum number of operations such that the prefix sum array does not contain negative
 * integers. The test cases are generated such that it is always possible to make the prefix sum
 * array non-negative.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int makePrefSumNonNegative(std::vector<int>& nums)
    {
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        long long presum = 0;
        int result = 0;
        for (const auto& val : nums) {
            presum += val;
            if (val < 0) {
                pq.push(val);
            }
            if (presum < 0) {
                presum -= pq.top();
                pq.pop();
                result++;
            }
        }
        return result;
    }
};
