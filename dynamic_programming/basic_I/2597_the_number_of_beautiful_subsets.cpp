#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of positive integers and a positive integer k.
 *
 * A subset of nums is beautiful if it does not contain two integers with an absolute difference
 * equal to k.
 *
 * Return the number of non-empty beautiful subsets of the array nums.
 *
 * A subset of nums is an array that can be obtained by deleting some (possibly none) elements from
 * nums. Two subsets are different if and only if the chosen indices to delete are different.
 *
 * ! 1 <= nums.length <= 20
 * ! 1 <= nums[i], k <= 1000
 */

class Solution {
public:
    int beautifulSubsets(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // DP, TC = O(NlogN), SC = O(N)
    int approach2(const std::vector<int>& nums, int k)
    {
        // if a%k != b%k, then both a and b can be picked
        // if a%k == b%k and |a-b| ==k, then a and b can not be picked at the same time
        std::unordered_map<int, int> count;
        for (const auto& val : nums) {
            count[val]++;
        }
        std::unordered_map<int, std::vector<int>> map;
        for (const auto& [val, freq] : count) {
            map[val % k].push_back(val);
        }
        int result = 1;
        for (auto& [key, group] : map) {
            std::sort(group.begin(), group.end());
            // similar to "House Robber"
            // group does not contain duplicate values
            // dp[i] = num of valid subsets of group[0:i-1]
            // - empty subset is valid
            // - non-empty subset must contain group[i-1]
            //   and must not contain group[i-1]-k
            const int n = group.size();
            std::vector<int> dp(n + 1, 0);
            dp[0] = 1;
            dp[1] = 1 << count[group[0]];
            for (int i = 2; i <= n; ++i) {
                const auto& curr = group[i - 1];
                const auto& prev = group[i - 2];
                if (curr - prev == k) {
                    // case 1.1: curr is not picked
                    // case 1.2: curr is picked and prev is not picked,
                    dp[i] = dp[i - 1] + dp[i - 2] * ((1 << count[curr]) - 1);
                } else {
                    // case 2.1: curr is not picked
                    // case 2.2: curr is picked
                    dp[i] = dp[i - 1] + dp[i - 1] * ((1 << count[curr]) - 1);
                }
            }
            result *= dp[n];
        }
        return result - 1; // subtract empty subset
    }

    // backtracking, TC = O(2^N), SC = O(N)
    int approach1(const std::vector<int>& nums, int k)
    {
        std::unordered_map<int, int> map;
        int result = 0;
        backtrack(result, map, 0, k, nums);
        return result - 1; // subtract empty subset
    }

    void backtrack(int& result, std::unordered_map<int, int>& map, int i, int k, const std::vector<int>& nums)
    {
        if (i == nums.size()) {
            result++;
            return;
        }
        backtrack(result, map, i + 1, k, nums);
        if (map[nums[i] + k] == 0 && map[nums[i] - k] == 0) {
            map[nums[i]]++;
            backtrack(result, map, i + 1, k, nums);
            map[nums[i]]--;
        }
    }
};