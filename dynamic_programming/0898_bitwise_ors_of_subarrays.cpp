#include <unordered_set>
#include <vector>

/**
 * Given an integer array arr, return the number of distinct bitwise ORs of all the non-empty
 * subarrays of arr.
 *
 * The bitwise OR of a subarray is the bitwise OR of each integer in the subarray. The bitwise OR of
 * a subarray of one integer is that integer.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= arr.length <= 5 * 10^4
 * ! 0 <= arr[i] <= 10^9
 */

class Solution {
public:
    int subarrayBitwiseORs(std::vector<int>& arr)
    {
        return approach2(arr);
    }

private:
    int approach2(const std::vector<int>& arr)
    {
        std::unordered_set<int> set;
        std::unordered_set<int> ors; // distinct ORs ending at arr[i]
        std::unordered_set<int> all;
        for (const auto& val : arr) {
            set.clear();
            set.insert(val);
            all.insert(val);
            for (const auto& v : ors) {
                set.insert(v | val);
                all.insert(v | val);
            }
            std::swap(ors, set);
        }
        return all.size();
    }

    int approach1(const std::vector<int>& arr)
    {
        // dp[i] = distince ORs of all non-empty subarrays of arr[0:i-1] ending at arr[i-1]
        const int n = arr.size();
        std::vector<std::unordered_set<int>> dp(n + 1);
        std::unordered_set<int> all;
        for (int i = 1; i <= n; ++i) {
            dp[i].insert(arr[i - 1]);
            for (const auto& v : dp[i - 1]) {
                dp[i].insert(arr[i - 1] | v);
            }
            all.insert(dp[i].begin(), dp[i].end());
        }
        return all.size();
    }
};
