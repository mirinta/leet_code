#include <unordered_map>
#include <vector>

/**
 * Given an integer array "arr" and an integer "difference", return the length of the longest
 * subsequence in "arr" which is an arithmetic sequence such that the difference between adjacent
 * elements in the subsequence equals "difference".
 *
 * A subsequence is a sequence that can be derived from "arr" by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 1 <= arr.length <= 10^5
 * ! -10^4 <= arr[i], difference <= 10^4
 */

class Solution {
public:
    int longestSubsequence(const std::vector<int>& arr, int difference)
    {
        if (arr.empty())
            return 0;

        // map[i] = num of LAS that ends with arr[i]
        // - for any i, the previous item is prev = arr[i] - difference
        // - if map[prev] is a solved subproblem, then map[i] = map[prev] + 1
        // - otherwise, {arr[i]}, LAS with single element, i.e., map[i] = 1
        std::unordered_map<int, int> map;
        int result = 0;
        for (const auto& val : arr) {
            if (!map.count(val - difference)) {
                map[val] = 1;
            } else {
                map[val] = map[val - difference] + 1;
            }
            result = std::max(result, map[val]);
        }
        return result;
    }
};