#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums consisting of unique integers.
 *
 * Originally, nums contained every integer within a certain range. However, some integers might have gone missing from
 * the array.
 *
 * The smallest and largest integers of the original range are still present in nums.
 *
 * Return a sorted list of all the missing integers in this range. If no integers are missing, return an empty list.
 *
 * ! 2 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    std::vector<int> findMissingElements(std::vector<int>& nums)
    {
        const int n = nums.size();
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& v : nums) {
            min = std::min(min, v);
            max = std::max(max, v);
        }
        std::unordered_set<int> set{nums.begin(), nums.end()};
        std::vector<int> result;
        result.reserve(max - min + 1 - n);
        for (int v = min; v <= max; ++v) {
            if (!set.count(v)) {
                result.emplace_back(v);
            }
        }
        return result;
    }
};