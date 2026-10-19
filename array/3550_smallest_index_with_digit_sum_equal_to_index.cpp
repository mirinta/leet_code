#include <vector>

/**
 * You are given an integer array nums.
 *
 * Return the smallest index i such that the sum of the digits of nums[i] is equal to i.
 *
 * If no such index exists, return -1.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 1000
 */

class Solution {
public:
    int smallestIndex(std::vector<int>& nums)
    {
        const int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (helper(nums[i]) == i)
                return i;
        }
        return -1;
    }

private:
    int helper(int n)
    {
        int result = 0;
        while (n) {
            result += n % 10;
            n /= 10;
        }
        return result;
    }
};
