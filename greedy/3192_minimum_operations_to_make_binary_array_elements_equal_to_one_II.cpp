#include <vector>

/**
 * You are given a binary array nums.
 *
 * You can do the following operation on the array any number of times (possibly zero):
 *
 * Choose any index i from the array and flip all the elements from index i to the end of the array.
 *
 * - Flipping an element means changing its value from 0 to 1, and from 1 to 0.
 *
 * Return the minimum number of operations required to make all elements in nums equal to 1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 1
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(const std::vector<int>& nums)
    {
        int flips = 0;
        for (const auto& val : nums) {
            if (((flips % 2) ^ val) == 0) {
                flips++;
            }
        }
        return flips;
    }

    int approach1(const std::vector<int>& nums)
    {
        // flips[i] = num of times that nums[i] is flipped
        // diff[i] = flips[i] - flips[i - 1]
        // then flips[i] = diff[0] + diff[1] + ... + diff[i]
        const int n = nums.size();
        std::vector<int> diff(n, 0);
        int result = 0;
        for (int i = 0, flips = 0; i < n; ++i) {
            flips += i > 0 ? diff[i - 1] : 0;
            if ((flips % 2) ^ nums[i])
                continue;

            diff[i]++;
            result++;
        }
        return result;
    }
};
