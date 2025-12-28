#include <array>
#include <vector>

/**
 * You are given an array nums consisting of integers. You are also given a 2D array queries, where
 * queries[i] = [posi, xi].
 *
 * For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which
 * is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
 *
 * Return the sum of the answers to all queries.
 *
 * Since the final answer may be very large, return it modulo 109 + 7.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! -10^5 <= nums[i] <= 10^5
 * ! 1 <= queries.length <= 5 * 10^4
 * ! queries[i] == [posi, xi]
 * ! 0 <= posi <= nums.length - 1
 * ! -10^5 <= xi <= 10^5
 */

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<int>& nums) : dp(4 * nums.size())
    {
        build(1, 1, nums.size(), nums);
    }

    void update(int id, int lo, int hi, int targetID, long long targetVal)
    {
        if (lo == hi) {
            dp[id][3] = targetVal;
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        if (targetID <= mid) {
            update(2 * id, lo, mid, targetID, targetVal);
        } else {
            update(2 * id + 1, mid + 1, hi, targetID, targetVal);
        }
        maintain(id);
    }

    long long query()
    {
        return std::max({dp[1][0], dp[1][1], dp[1][2], dp[1][3]});
    }

private:
    void build(int id, int lo, int hi, const std::vector<int>& nums)
    {
        if (lo == hi) {
            dp[id] = {0, LLONG_MIN / 4, LLONG_MIN / 4, nums[lo - 1]};
            return;
        }
        const int mid = lo + (hi - lo) / 2;
        build(2 * id, lo, mid, nums);
        build(2 * id + 1, mid + 1, hi, nums);
        maintain(id);
    }

    void maintain(int id)
    {
        const int l = 2 * id;
        const int r = 2 * id + 1;
        dp[id][0] = std::max({dp[l][0] + dp[r][0], dp[l][0] + dp[r][2], dp[l][1] + dp[r][0]});
        dp[id][1] = std::max({dp[l][0] + dp[r][1], dp[l][0] + dp[r][3], dp[l][1] + dp[r][1]});
        dp[id][2] = std::max({dp[l][2] + dp[r][0], dp[l][2] + dp[r][2], dp[l][3] + dp[r][0]});
        dp[id][3] = std::max({dp[l][2] + dp[r][1], dp[l][2] + dp[r][3], dp[l][3] + dp[r][1]});
    }

private:
    // dp[0] = dp00, dp[1] = dp01, dp[2] = dp10, dp[3] = dp11
    std::vector<std::array<long long, 4>> dp;
};

class Solution {
public:
    int maximumSumSubsequence(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        // key methodology: house robber + divide conquer
        //
        // dp00[i][j] = max sum of a subsequence of nums[i:j] while nums[i] and nums[j] are not
        // picked
        //
        // dp01[i][j] = max sum of a subsequence of nums[i:j] while nums[j] is picked and nums[j] is
        // not picked
        //
        // dp10[i][j] = max sum of a subsequence of nums[i:j] while only nums[i] is picked and
        // nums[j] is not picked
        //
        // dp11[i][j] = max sum of a subsequence of nums[i:j] while nums[i] and nums[j] are picked
        //
        // for any k where i <= k <= j
        // [i ... k] [k+1 ... j]
        // dp00[i][j] = max of (dp00[i][k] + dp00[k+1][j],
        //                      dp00[i][k] + dp10[k+1][j],
        //                      dp01[i][k] + dp00[k+1][j])
        //
        // dp01[i][j] = max of (dp00[i][k] + dp01[k+1][j],
        //                      dp00[i][k] + dp11[k+1][j],
        //                      dp01[i][k] + dp01[k+1][j])
        //
        // dp10[i][j] = max of (dp10[i][k] + dp00[k+1][j],
        //                      dp10[i][k] + dp10[k+1][j],
        //                      dp11[i][k] + dp00[k+1][j])
        //
        // dp11[i][j] = max of (dp10[i][k] + dp01[k+1][j],
        //                      dp10[i][k] + dp11[k+1][j],
        //                      dp11[i][k] + dp01[k+1][j])
        //
        // corner cases:
        // dp00[i][i] = 0
        // dp11[i][i] = nums[i]
        // dp01[i][i] = MIN
        // dp10[i][i] = MIN
        constexpr long long kMod = 1e9 + 7;
        const int n = nums.size();
        SegmentTree tree(nums);
        long long result = 0;
        for (const auto& query : queries) {
            tree.update(1, 1, n, query[0] + 1, query[1]);
            result = (result + tree.query()) % kMod;
        }
        return result;
    }
};