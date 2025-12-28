#include <unordered_map>
#include <vector>

/**
 * You are given an array of positive integers nums.
 *
 * You need to select a subset of nums which satisfies the following condition:
 *
 * - You can place the selected elements in a 0-indexed array such that it follows the pattern: [x,
 * x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] (Note that k can be be any non-negative power of 2).
 * For example, [2, 4, 16, 4, 2] and [3, 9, 3] follow the pattern while [2, 4, 8, 4, 2] does not.
 *
 * Return the maximum number of elements in a subset that satisfies these conditions.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int maximumLength(std::vector<int>& nums)
    {
        std::unordered_map<long long, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        int result = 0;
        if (map.count(1)) {
            result = map[1] % 2 != 0 ? map[1] : map[1] - 1;
            map.erase(1);
        }
        for (const auto& [val, freq] : map) {
            int length = 0;
            long long base = val;
            while (true) {
                if (!map.count(base)) {
                    length -= 1;
                    break;
                }
                if (map[base] == 1) {
                    length += 1;
                    break;
                }
                length += 2;
                base *= base;
            }
            result = std::max(result, length);
        }
        return result;
    }
};