#include <array>
#include <vector>

class Solution {
public:
    long long maximumValueSum(std::vector<int>& nums, int k, std::vector<std::vector<int>>& edges)
    {
        // apply operation on edge(u,v): nums[u]' = nums[u] ^ k, nums[v]' = nums[v] ^ k
        // apply operation on edge(v,w): nums[v]'' = nums[v]' ^ k = nums[v], nums[w]' = nums[w] ^ k
        // ...
        // if two nodes x and y are connected,
        // their values can be modified without changing other nodes
        //
        // thus, the problem is equivalent to "find the max sum by changing an even num of nodes"
        const int n = nums.size();
        // dp[i][0] = max sum of nums[0:i] by changing an even num of nodes
        // dp[i][1] = max sum of nums[0:i] by changing an odd num of nodes
        std::vector<std::array<long long, 2>> dp(n, {0, 0});
        dp[0][0] = nums[0];
        dp[0][1] = nums[0] ^ k;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = std::max(dp[i - 1][0] + nums[i], dp[i - 1][1] + (nums[i] ^ k));
            dp[i][1] = std::max(dp[i - 1][1] + nums[i], dp[i - 1][0] + (nums[i] ^ k));
        }
        return dp[n - 1][0];
    }
};
