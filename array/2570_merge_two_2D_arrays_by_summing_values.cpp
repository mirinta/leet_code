#include <map>
#include <vector>

/**
 * You are given two 2D integer arrays nums1 and nums2.
 *
 * - nums1[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
 *
 * - nums2[i] = [idi, vali] indicate that the number with the id idi has a value equal to vali.
 *
 * Each array contains unique ids and is sorted in ascending order by id.
 *
 * Merge the two arrays into one array that is sorted in ascending order by id, respecting the
 * following conditions:
 *
 * - Only ids that appear in at least one of the two arrays should be included in the resulting
 * array.
 *
 * - Each id should be included only once and its value should be the sum of the values of this id
 * in the two arrays. If the id does not exist in one of the two arrays, then assume its value in
 * that array to be 0.
 *
 * Return the resulting array. The returned array must be sorted in ascending order by id.
 *
 * ! 1 <= nums1.length, nums2.length <= 200
 * ! nums1[i].length == nums2[j].length == 2
 * ! 1 <= idi, vali <= 1000
 * ! Both arrays contain unique ids.
 * ! Both arrays are in strictly ascending order by id.
 */

class Solution
{
public:
    std::vector<std::vector<int>> mergeArrays(std::vector<std::vector<int>>& nums1,
                                              std::vector<std::vector<int>>& nums2)
    {
        std::map<int, int> map;
        for (const auto& pair : nums1) {
            map[pair[0]] = pair[1];
        }
        for (const auto& pair : nums2) {
            map[pair[0]] += pair[1];
        }
        std::vector<std::vector<int>> result;
        result.reserve(map.size());
        for (const auto& [k, v] : map) {
            result.push_back({k, v});
        }
        return result;
    }
};
