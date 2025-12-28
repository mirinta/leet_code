#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
 *
 * We make a binary tree using these integers, and each number may be used for any number of times.
 * Each non-leaf node's value should be equal to the product of the values of its children.
 *
 * Return the number of binary trees we can make. The answer may be too large so return the answer
 * modulo 10^9 + 7.
 *
 * ! 1 <= arr.length <= 1000
 * ! 2 <= arr[i] <= 10^9
 * ! All the values of arr are unique.
 */

class Solution {
public:
    int numFactoredBinaryTrees(std::vector<int>& arr)
    {
        constexpr int kMod = 1e9 + 7;
        const int n = arr.size();
        std::sort(arr.begin(), arr.end()); // #NOTE# all values are unique
        std::unordered_map<int, int> map;  // val to index
        for (int i = 0; i < n; ++i) {
            map[arr[i]] = i;
        }
        // dp[i] = num of binary trees that use nums[i] as root node
        std::vector<long> dp(n, 1);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (arr[i] % arr[j] != 0)
                    continue;

                const int fraction = arr[i] / arr[j];
                if (map.count(fraction)) {
                    dp[i] = (dp[i] + dp[j] * dp[map[fraction]]) % kMod;
                }
            }
            result = (result + dp[i]) % kMod;
        }
        return result;
    }
};