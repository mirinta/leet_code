#include <vector>

/**
 * Given an array of integers, return the maximum sum ofr a non-empty subarray (contiguous elements)
 * with at most one element deletion. In other words, you want to choose a subarray and optionally
 * delete one element from it so that there is still at least one element left and the sum of the
 * remaining elements is maximum possible.
 *
 * ! 1 <= arr.length <= 105
 * ! -10^4 <= arr[i] <= 10^4
 */

class Solution {
public:
    int maximumSum(std::vector<int>& arr)
    {
        if (arr.size() <= 1)
            return arr.empty() ? INT_MIN : arr[0];

        // optimize space complexity:
        // in approach 1,we see that
        // - dp[i][0] is dependent on dp[i-1][0], and
        // - dp[i][1] is dependent on dp[i-1][0] and dp[i-1][1]
        // - dp[i-1][0] represents the last round without deletion, and
        //   dp[i-1][1] represents the last round with deletion
        const auto n = arr.size();
        int withDeletion = 0;
        int withoutDeletion = arr[0];
        int result = INT_MIN;
        for (int i = 1; i < n; ++i) {
            withDeletion = std::max(withoutDeletion, withDeletion + arr[i]); // dp[i][1]
            withoutDeletion = std::max(withoutDeletion + arr[i], arr[i]);    // dp[i][0]
            result = std::max({result, withDeletion, withoutDeletion});
        }
        return result;
    }

private:
    int approach1(std::vector<int>& arr)
    {
        if (arr.size() <= 1)
            return arr.empty() ? INT_MIN : arr[0];

        // dp[i][0] = max sum of subarray that ends with the ith element without any deletion
        // dp[i][1] = max sum of subarray that ends with the ith element with one deletion
        // base cases:
        // - dp[0][0] = arr[0], only one element and no deletion
        // - dp[0][1] = 0, no element
        const auto n = arr.size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(2, 0));
        dp[0][0] = arr[0];
        int result = INT_MIN;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0] + arr[i], arr[i]);
            dp[i][1] = std::max(dp[i - 1][0], dp[i - 1][1] + arr[i]);
            result = std::max({result, dp[i][0], dp[i][1]});
        }
        return result;
    }
};