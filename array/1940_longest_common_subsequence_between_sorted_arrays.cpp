#include <unordered_map>
#include <vector>

/**
 * Given an array of integer arrays arrays where each arrays[i] is sorted in strictly increasing
 * order, return an integer array representing the longest common subsequence between all the
 * arrays.
 *
 * A subsequence is a sequence that can be derived from another sequence by deleting some elements
 * (possibly none) without changing the order of the remaining elements.
 *
 * ! 2 <= arrays.length <= 100
 * ! 1 <= arrays[i].length <= 100
 * ! 1 <= arrays[i][j] <= 100
 * ! arrays[i] is sorted in strictly increasing order.
 */

class Solution {
public:
    std::vector<int> longestCommonSubsequence(std::vector<std::vector<int>>& arrays)
    {
        const int n = arrays.size();
        std::unordered_map<int, int> map;
        std::vector<int> result;
        for (const auto& arr : arrays) {
            for (const auto& val : arr) {
                map[val]++;
                if (map[val] == n) {
                    result.push_back(val);
                }
            }
        }
        return result;
    }
};