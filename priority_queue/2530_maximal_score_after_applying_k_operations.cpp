#include <cmath>
#include <queue>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and an integer k. You have a starting score of 0.
 *
 * In one operation:
 *
 * 1. choose an index i such that 0 <= i < nums.length,
 *
 * 2. increase your score by nums[i], and
 *
 * 3. replace nums[i] with ceil(nums[i] / 3).
 *
 * Return the maximum possible score you can attain after applying exactly k operations.
 *
 * The ceiling function ceil(val) is the least integer greater than or equal to val.
 *
 * ! 1 <= nums.length, k <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long maxKelements(std::vector<int>& nums, int k)
    {
        std::priority_queue<int> pq;
        for (const auto& val : nums) {
            pq.push(val);
        }
        long long result = 0;
        while (k-- && !pq.empty()) {
            const auto top = pq.top();
            pq.pop();
            result += top;
            pq.push(std::ceil(top * 1.0 / 3));
        }
        return result;
    }
};