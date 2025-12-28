#include <unordered_map>
#include <vector>

/**
 * Given an array nums of distinct positive integers, return the number of tuples (a, b, c, d) such
 * that a * b = c * d where a, b, c, and d are elements of nums, and a != b != c != d.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^4
 * ! All elements in nums are distinct.
 */

class Solution {
public:
    int tupleSameProduct(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                map[nums[i] * nums[j]]++;
            }
        }
        int result = 0;
        for (const auto& [product, count] : map) {
            result += count * (count - 1) * 4;
        }
        return result;
    }
};