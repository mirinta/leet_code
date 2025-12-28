#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed array nums consisting of positive integers.
 *
 * There are two types of operations that you can apply on the array any number of times:
 *
 * - Choose two elements with equal values and delete them from the array.
 *
 * - Choose three elements with equal values and delete them from the array.
 *
 * Return the minimum number of operations required to make the array empty, or -1 if it is not
 * possible.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        int result = 0;
        for (const auto& [val, count] : map) {
            if (count == 1)
                return -1;

            // delete 3 equal elements as much as possible
            result += count / 3;
            result += std::ceil((count % 3) * 1.0 / 2);
        }
        return result;
    }
};