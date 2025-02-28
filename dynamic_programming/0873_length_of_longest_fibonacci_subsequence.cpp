#include <unordered_map>
#include <vector>

/**
 * A sequence x1, x2, ..., xn is Fibonacci-like if:
 *
 * - n >= 3
 *
 * - xi + xi+1 == xi+2 for all i + 2 <= n
 *
 * Given a strictly increasing array arr of positive integers forming a sequence, return the length
 * of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.
 *
 * A subsequence is derived from another sequence arr by deleting any number of elements (including
 * none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a
 * subsequence of [3, 4, 5, 6, 7, 8].
 *
 * ! 3 <= arr.length <= 1000
 * ! 1 <= arr[i] < arr[i + 1] <= 10^9
 */

class Solution
{
public:
    int lenLongestFibSubseq(std::vector<int>& arr)
    {
        // dp[i][j] = length of the longest Fib subsequence of arr[0:i]
        // while the last two elements are arr[j] and arr[i]
        const int n = arr.size();
        std::unordered_map<int, int> map; // value to index
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                const int diff = arr[i] - arr[j];
                if (map.count(diff) && arr[j] > diff) {
                    dp[i][j] = std::max(dp[i][j], dp[j][map[diff]] + 1);
                    result = std::max(result, dp[i][j]);
                } else {
                    dp[i][j] = 2;
                }
            }
            map[arr[i]] = i;
        }
        return result;
    }
};
