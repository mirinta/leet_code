#include <set>
#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr, replace each element with its rank.
 *
 * The rank represents how large the element is. The rank has the following rules:
 *
 * - Rank is an integer starting from 1.
 *
 * - The larger the element, the larger the rank. If two elements are equal, their rank must be the
 * same.
 *
 * - Rank should be as small as possible.
 *
 * ! 0 <= arr.length <= 10^5
 * ! -10^9 <= arr[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> arrayRankTransform(std::vector<int>& arr)
    {
        std::set<int> set(arr.begin(), arr.end());
        int rank = 1;
        std::unordered_map<int, int> map;
        for (const auto& val : set) {
            map[val] = rank++;
        }
        std::vector<int> result(arr.size());
        for (int i = 0; i < arr.size(); ++i) {
            result[i] = map[arr[i]];
        }
        return result;
    }
};