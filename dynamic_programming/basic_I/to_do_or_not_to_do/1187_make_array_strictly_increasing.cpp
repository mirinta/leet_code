#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * Given two integer arrays arr1 and arr2, return the minimum number of operations (possibly zero)
 * needed to make arr1 strictly increasing.
 *
 * In one operation, you can choose two indices 0 <= i < arr1.length and 0 <= j < arr2.length and do
 * the assignment arr1[i] = arr2[j].
 *
 * If there is no way to make arr1 strictly increasing, return -1.
 *
 * ! 1 <= arr1.length, arr2.length <= 2000
 * ! 0 <= arr1[i], arr2[i] <= 10^9
 */

class Solution {
public:
    int makeArrayIncreasing(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        std::sort(arr2.begin(), arr2.end());
        std::vector<std::unordered_map<int, int>> memo(arr1.size());
        const int result = dfs(memo, 0, -1, arr1, arr2);
        return result == INT_MAX / 2 ? -1 : result;
    }

private:
    // min num of operations to make arr1[i:n-1] strictly increasing
    int dfs(std::vector<std::unordered_map<int, int>>& memo,
            int i,
            int prev,
            const std::vector<int>& arr1,
            const std::vector<int>& arr2)
    {
        if (i == arr1.size())
            return 0;

        if (memo[i].count(prev))
            return memo[i][prev];

        int result = INT_MAX / 2;
        if (arr1[i] > prev) {
            result = std::min(result, dfs(memo, i + 1, arr1[i], arr1, arr2));
        }
        auto iter = std::upper_bound(arr2.begin(), arr2.end(), prev);
        if (iter != arr2.end()) {
            result = std::min(result, 1 + dfs(memo, i + 1, *iter, arr1, arr2));
        }
        return memo[i][prev] = result;
    }
};