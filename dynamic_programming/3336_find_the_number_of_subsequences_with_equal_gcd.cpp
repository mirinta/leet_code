#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * Your task is to find the number of pairs non-empty subsequences (seq1, seq2) of nums that satisfy the following
 * conditions:
 *
 * - The subsequences seq1 and seq2 are disjoint, meaning non index of nums is common between them.
 *
 * - The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
 *
 * Return the total number of such pairs.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= 200
 */

class Solution {
public:
    int subsequencePairCount(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int max = *std::max_element(nums.begin(), nums.end());
        Memo memo(n, std::vector<std::vector<int>>(max + 1, std::vector<int>(max + 1, -1)));
        return std::max(0, dfs(memo, 0, 0, 0, nums) - 1); // except empty subsequence
    }

private:
    static constexpr int kMod = 1e9 + 7;

    using Memo = std::vector<std::vector<std::vector<int>>>;

    // num of valid pairs of nums[0:i]
    // while gcd(seq1) = j and gcd(seq2) = k
    int dfs(Memo& memo, int i, int j, int k, const std::vector<int>& nums)
    {
        if (i == nums.size())
            return j == k;

        if (memo[i][j][k] != -1)
            return memo[i][j][k];

        int result = dfs(memo, i + 1, j, k, nums);
        result = (result + dfs(memo, i + 1, j, std::gcd(k, nums[i]), nums)) % kMod;
        result = (result + dfs(memo, i + 1, std::gcd(j, nums[i]), k, nums)) % kMod;
        return memo[i][j][k] = result;
    }
};