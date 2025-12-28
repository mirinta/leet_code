#include <array>
#include <vector>

/**
 * You are given an array nums and an integer k. You need to find a subarray of nums such that the
 * absolute difference between k and the bitwise AND of the subarray elements is as small as
 * possible. In other words, select a subarray nums[l..r] such that |k - (nums[l] AND nums[l + 1]
 * ... AND nums[r])| is minimum.
 *
 * Return the minimum possible value of the absolute difference.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    int minimumDifference(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<std::array<int, 31>> count(n + 1);
        for (int i = 1; i <= n; ++i) {
            count[i] = count[i - 1];
            for (int j = 0; j < 31; ++j) {
                if (nums[i - 1] >> j & 1) {
                    count[i][j]++;
                }
            }
        }
        auto query = [&count](int left, int right) {
            int result = 0;
            for (int j = 0; j < 31; ++j) {
                const int setBits = count[right + 1][j] - count[left][j];
                if (setBits == right - left + 1) {
                    result |= 1 << j;
                }
            }
            return result;
        };
        int result = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            while (left <= right && query(left, right) < k) {
                result = std::min(result, std::abs(query(left, right) - k));
                left++;
            }
            result = std::min(result, std::abs(query(left, right) - k));
        }
        return result;
    }
};