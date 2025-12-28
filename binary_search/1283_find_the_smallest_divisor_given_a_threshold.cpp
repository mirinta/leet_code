#include <algorithm>
#include <cmath>
#include <vector>

/**
 * Given an array of integers nums and an integer threshold, we will choose a positive integer
 * divisor, divide all the array by it, and sum the division's result. Find the smallest divisor
 * such that the result mentioned above is less than or equal to threshold.
 *
 * Each result of the division is rounded to the nearest integer greater than or equal to that
 * element. (For example: 7/3 = 3 and 10/2 = 5).
 *
 * The test cases are generated so that there will be an answer.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 1 <= nums[i] <= 10^6
 * ! nums.length <= threshold <= 10^6
 */

class Solution {
public:
    int smallestDivisor(std::vector<int>& nums, int threshold)
    {
        int lo = 1;
        int hi = *std::max_element(nums.begin(), nums.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, threshold)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int divisor, const std::vector<int>& nums, int threshold)
    {
        int sum = 0;
        for (const auto& val : nums) {
            sum += std::ceil(val * 1.0 / divisor);
            if (sum > threshold)
                return false;
        }
        return true;
    }
};