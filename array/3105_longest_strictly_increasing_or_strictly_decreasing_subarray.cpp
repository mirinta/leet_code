#include <vector>

/**
 * You are given an array of integers nums. Return the length of the longest subarray of nums which
 * is either strictly increasing or strictly decreasing.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    int longestMonotonicSubarray(std::vector<int>& nums)
    {
        return std::max(helper(nums, std::greater<>()), helper(nums, std::less<>()));
    }

private:
    template<typename Compare>
    int helper(const std::vector<int>& nums, Compare compare)
    {
        const int n = nums.size();
        int i = 0;
        int result = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && compare(nums[j], nums[j - 1])) {
                j++;
            }
            result = std::max(result, j - i);
            i = j;
        }
        return result;
    }
};