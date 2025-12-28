#include <vector>

/**
 * You are given an integer array nums consisting of n elements, and an integer k.
 *
 * Find a contiguous subarray whose length is greater than or equal to k that has the maximum
 * average value and return this value. Any answer with a calculation error less than 10^-5 will be
 * accepted.
 *
 * ! n == nums.length
 * ! 1 <= k <= n <= 10^4
 * ! -10^4 <= nums[i] <= 10^4
 */

class Solution {
public:
    double findMaxAverage(std::vector<int>& nums, int k)
    {
        // guess the max average value
        double lo = INT_MAX;
        double hi = INT_MIN;
        for (const auto& val : nums) {
            lo = std::min<int>(lo, val);
            hi = std::max<int>(hi, val);
        }
        while (hi - lo > 1e-5) {
            const double mid = lo + (hi - lo) / 2;
            if (isValid(mid, k, nums)) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return lo;
    }

private:
    bool isValid(double average, int k, const std::vector<int>& nums)
    {
        // check if there exists a subarray with length >= k and its average value >= average
        // extract average from nums[i], then we need to find a subarray with length >= k and its
        // sum >= 0 0 X X X X X X X i-1 i X X X X j
        // |<-prefix[0:i-1]->| |<-check->|
        // |<--------prefix[0:j]-------->|
        double prefixSum = 0;
        for (int i = 0; i < k; ++i) {
            prefixSum += nums[i] - average; // the subarray must have at least k elements
        }
        if (prefixSum >= 0)
            return true;

        double prev = 0;
        double minPrev = 0;
        for (int i = k; i < nums.size(); ++i) {
            prefixSum += nums[i] - average;
            prev += nums[i - k] - average;
            minPrev = std::min(minPrev, prev);
            if (prefixSum - minPrev >= 0)
                return true;
        }
        return false;
    }
};
