#include <array>
#include <vector>

/**
 * Given an array of integers nums and an integer k, return the number of subarrays of nums where
 * the bitwise AND of the elements of the subarray equals k.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i], k <= 10^9
 */

class Solution {
public:
    long long countSubarrays(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        // count[i][j] = num of elements of nums[0:i] such that the jth bit of each element is 1
        std::vector<std::array<int, 32>> count(n);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                count[i] = count[i - 1];
            }
            for (int j = 0; j < 32; ++j) {
                count[i][j] += (nums[i] >> j) & 1;
            }
        }
        return solve(nums, k, count) - solve(nums, k + 1, count);
    }

private:
    // bitwise AND of nums[left:right]
    int query(int left, int right, const std::vector<std::array<int, 32>>& count)
    {
        if (left > right)
            return 0;

        int result = 0;
        for (int j = 0; j < 32; ++j) {
            const int setbits = count[right][j] - (left > 0 ? count[left - 1][j] : 0);
            if (setbits == right - left + 1) {
                result |= 1 << j;
            }
        }
        return result;
    }

    // num of subarrays of nums where the bitwise AND of the elements of the subarray >= k
    long long solve(const std::vector<int>& nums, int k, const std::vector<std::array<int, 32>>& count)
    {
        const int n = nums.size();
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (left <= right && query(left, right, count) < k) {
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};