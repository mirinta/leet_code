#include <algorithm>
#include <vector>

/**
 * Given an array of distinct integers "arr", find all pairs of elements with the minimum absolute
 * difference of any two elements.
 *
 * Return a list of pairs in ascending order (with respect to pairs), each pair [a, b] follows:
 *
 * - a, b are from "arr"
 *
 * - a < b
 *
 * - b - a equals to the minimum absolute difference of any two elements in "arr".
 */

class Solution {
public:
    std::vector<std::vector<int>> minimumAbsDifference(std::vector<int>& arr)
    {
        if (arr.size() < 2)
            return {};

        std::vector<std::vector<int>> result;
        std::sort(arr.begin(), arr.end());
        int minAbsDiff = INT_MAX;
        for (size_t i = 1; i < arr.size(); ++i) {
            const auto absDiff = arr[i] - arr[i - 1];
            if (absDiff < minAbsDiff) {
                result.clear();
                minAbsDiff = absDiff;
            }
            if (absDiff <= minAbsDiff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }
        return result;
    }
};