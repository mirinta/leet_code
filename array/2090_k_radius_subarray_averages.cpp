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
 * For example, the average of four elements 2, 3, 1, and 5 is (2 + 3 + 1 + 5) / 4 = 11 / 4 = 2.75,
 * which truncates to 2.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums[i], k <= 10^5
 */

class Solution
{
public:
    std::vector<int> getAverages(std::vector<int>& nums, int k)
    {
        if (nums.empty() || k == 0)
            return nums;

        const int n = nums.size();
        // 0...[i-k...i...i+k]...END
        // fixed window size = 2k+1
        std::vector<int> result(nums.size(), -1);
        const int windowSize = 2 * k + 1;
        if (windowSize > n)
            return result;

        // each time the window moves,
        // nums[i+k] comes in and nums[i-k-1] comes out
        // initialize windowSum:
        // index:  X 0...i...2k-1 2k
        //         | init value |
        long long windowSum = nums[0];
        for (int i = 0; i < 2 * k; ++i) {
            windowSum += nums[i];
        }
        for (int i = k; i < n - k; ++i) {
            windowSum -= i == k ? nums[0] : nums[i - k - 1];
            windowSum += nums[i + k];
            result[i] = windowSum / windowSize;
        }
        return result;
    }
};