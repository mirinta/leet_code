#include <algorithm>
#include <vector>

/**
 * Given an array of integers arr and an integer d. In one step you can jump from index i to index:
 *
 * - i + x where: i + x < arr.length and  0 < x <= d.
 *
 * - i - x where: i - x >= 0 and  0 < x <= d.
 *
 * In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for
 * all indices k between i and j (More formally min(i, j) < k < max(i, j)).
 *
 * You can choose any index of the array and start jumping. Return the maximum number of indices you
 * can visit.
 *
 * Notice that you can not jump outside of the array at any time.
 *
 * ! 1 <= arr.length <= 1000
 * ! 1 <= arr[i] <= 10^5
 * ! 1 <= d <= arr.length
 */

class Solution {
public:
    int maxJumps(std::vector<int>& arr, int d)
    {
        return approach2(arr, d);
    }

private:
    // time O(ND), space O(N)
    int approach2(const std::vector<int>& arr, int d)
    {
        const int n = arr.size();
        std::vector<int> memo(n, -1);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = std::max(result, dfs(memo, i, d, arr));
        }
        return result;
    }

    int dfs(std::vector<int>& memo, int i, int d, const std::vector<int>& arr)
    {
        if (memo[i] != -1)
            return memo[i];

        int result = 1;
        const int n = arr.size();
        for (int j = i + 1; j <= std::min(n - 1, i + d); ++j) {
            if (arr[j] >= arr[i])
                break;

            result = std::max(result, 1 + dfs(memo, j, d, arr));
        }
        for (int j = i - 1; j >= std::max(0, i - d); --j) {
            if (arr[j] >= arr[i])
                break;

            result = std::max(result, 1 + dfs(memo, j, d, arr));
        }
        memo[i] = result;
        return result;
    }

    // time (NlogN+ND), space O(N)
    int approach1(const std::vector<int>& arr, int d)
    {
        const int n = arr.size();
        std::vector<std::pair<int, int>> pairs; // <value, index>
        pairs.reserve(n);
        for (int i = 0; i < n; ++i) {
            pairs.emplace_back(arr[i], i);
        }
        std::sort(pairs.begin(), pairs.end());
        // dp[i] = max num of indices we can visit starting from index i
        // base case: dp[i] = 1, at least visit itself
        std::vector<int> dp(n, 1);
        int result = 1;
        for (int k = 1; k < n; ++k) {
            const auto& [height, i] = pairs[k];
            for (int j = i + 1; j <= std::min(n - 1, i + d); ++j) {
                if (arr[j] >= height)
                    break;

                dp[i] = std::max(dp[i], 1 + dp[j]);
            }
            for (int j = i - 1; j >= std::max(0, i - d); --j) {
                if (arr[j] >= height)
                    break;

                dp[i] = std::max(dp[i], 1 + dp[j]);
            }
            result = std::max(result, dp[i]);
        }
        return result;
    }
};
