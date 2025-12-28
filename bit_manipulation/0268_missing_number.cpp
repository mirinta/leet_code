#include <numeric>
#include <vector>

/**
 * Given an array nums containing n distinct numbers in the range [0, n], return the only number in
 * the range that is missing from the array.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^4
 * ! 0 <= nums[i] <= n
 * ! All the numbers of nums are unique.
 */

class Solution {
public:
    int missingNumber(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = n;
        for (int i = 0; i < n; ++i) {
            result ^= nums[i] ^ i;
        }
        return result;
    }

    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return n * (n + 1) / 2 - sum;
    }
};