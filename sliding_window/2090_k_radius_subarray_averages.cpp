#include <vector>

/**
 * You are given a 0-indexed array nums of n integers, and an integer k.
 *
 * The k-radius average for a subarray of nums centered at some index i with the radius k is the
 * average of all elements in nums between the indices i - k and i + k (inclusive). If there are
 * less than k elements before or after the index i, then the k-radius average is -1.
 *
 * Build and return an array avgs of length n where avgs[i] is the k-radius average for the subarray
 * centered at index i.
 *
 * The average of x elements is the sum of the x elements divided by x, using integer division. The
 * integer division truncates toward zero, which means losing its fractional part.
 *
 * - For example, the average of four elements 2, 3, 1, and 5 is (2 + 3 + 1 + 5) / 4 = 11 / 4
 * = 2.75, which truncates to 2.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums[i], k <= 10^5
 */

class Solution {
public:
    std::vector<int> getAverages(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // sliding window, TC = O(N), SC = O(1)
    std::vector<int> approach2(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const int L = 2 * k + 1;
        long long sum = 0;
        std::vector<int> result(n, -1);
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            if (right - left + 1 > L) {
                sum -= nums[left++];
            }
            if (right - left + 1 == L) {
                result[left + L / 2] = sum / L;
            }
        }
        return result;
    }

    // prefix sum, TC = O(N), SC = O(N)
    std::vector<int> approach1(const std::vector<int>& nums, int k)
    {
        // given a subarray nums[i-k:i+k]
        // if i-k >= 0 && i+k < n, the k-radius = (presum[i+k+1]-presum[i-k])/(2k+1)
        // otherwise, the k-radius = -1
        const int n = nums.size();
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            if (i - k >= 0 && i + k < n) {
                result[i] = (presum[i + k + 1] - presum[i - k]) / (2 * k + 1);
            } else {
                result[i] = -1;
            }
        }
        return result;
    }
};