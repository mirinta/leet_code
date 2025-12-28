#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, your goal is to make all elements in nums equal. To complete one
 * operation, follow these steps:
 *
 * 1. Find the largest value in nums. Let its index be i (0-indexed) and its value be largest. If
 * there are multiple elements with the largest value, pick the smallest i.
 *
 * 2. Find the next largest value in nums strictly smaller than largest. Let its value be
 * nextLargest.
 *
 * 3. Reduce nums[i] to nextLargest.
 *
 * Return the number of operations to make all elements in nums equal.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 1 <= nums[i] <= 5 * 10^4
 */

class Solution {
public:
    int reductionOperations(std::vector<int>& nums)
    {
        // assume x < y < z
        // #x, #y and #z are the frequencies of x, y and z
        // - perform #z operations to make z equal y, then #y+=#z
        // - perform #z+#y operations to make y equal x
        // - thus, the total num of operations = #y+#z+#z
        // X X X Y Y Y Y Z Z
        std::sort(nums.begin(), nums.end());
        int result = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] != nums[i - 1]) {
                result += nums.size() - i;
            }
        }
        return result;
    }
};