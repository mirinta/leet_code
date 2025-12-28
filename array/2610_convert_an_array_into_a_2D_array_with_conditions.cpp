#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums. You need to create a 2D array from nums satisfying the
 * following conditions:
 *
 * - The 2D array should contain only the elements of the array nums.
 *
 * - Each row in the 2D array contains distinct integers.
 *
 * - The number of rows in the 2D array should be minimal.
 *
 * Return the resulting array. If there are multiple answers, return any of them.
 *
 * Note that the 2D array can have a different number of elements on each row.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= nums.length
 */

class Solution {
public:
    std::vector<std::vector<int>> findMatrix(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        std::vector<std::vector<int>> result;
        while (!map.empty()) {
            std::vector<int> row;
            auto iter = map.begin();
            while (iter != map.end()) {
                row.push_back(iter->first);
                if (--(iter->second) == 0) {
                    iter = map.erase(iter);
                } else {
                    iter++;
                }
            }
            result.push_back(row);
        }
        return result;
    }
};