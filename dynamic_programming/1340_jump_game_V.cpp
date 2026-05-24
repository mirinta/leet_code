#include <algorithm>
#include <functional>
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
        const int n = arr.size();
        std::vector<int> memo(n, -1);
        std::function<int(int)> dfs = [&](int i) {
            if (memo[i] != -1)
                return memo[i];

            int result = 1;
            for (int j = i + 1; j <= std::min(i + d, n - 1); ++j) {
                if (arr[i] <= arr[j])
                    break;

                result = std::max(result, 1 + dfs(j));
            }
            for (int j = i - 1; j >= std::max(i - d, 0); --j) {
                if (arr[i] <= arr[j])
                    break;

                result = std::max(result, 1 + dfs(j));
            }
            return memo[i] = result;
        };
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = std::max(result, dfs(i));
        }
        return result;
    }
};
