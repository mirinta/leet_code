#include <vector>

/**
 * You are given an array nums which is a permutation of [0, 1, 2, ..., n - 1]. The score of any
 * permutation of [0, 1, 2, ..., n - 1] named perm is defined as:
 *
 * score(perm) = |perm[0] - nums[perm[1]]| + |perm[1] - nums[perm[2]]| + ... + |perm[n - 1] -
 * nums[perm[0]]|
 *
 * Return the permutation perm which has the minimum possible score. If multiple permutations exist
 * with this score, return the one that is lexicographically smallest among them.
 *
 * ! 2 <= n == nums.length <= 14
 * ! nums is a permutation of [0, 1, 2, ..., n - 1].
 */

class Solution {
public:
    std::vector<int> findPermutation(std::vector<int>& nums)
    {
        // score =   |perm[0]-nums[perm[1]]|
        //         + |perm[1]-nums[perm[2]]|
        //         + ...
        //         + |perm[n-2]-nums[perm[n-1]]|
        //         + |perm[n-1]-nums[perm[0]]|
        //
        // if we rotate the given perm by 1 position,
        // then perm' = {perm[n-1], perm[0], ..., perm[n-2]}
        //
        // score' =   |perm[n-1]-nums[perm[0]]|
        //          + |perm[0]-nums[perm[1]]|
        //          + ...
        //          + |perm[n-2]-nums[perm[n-1]]
        //
        // score = score', it means that rotating perm doesn't change the final score
        // our goal is to find the lexicographically smallest permutation,
        // then we can rotate perm to make perm[0] = 0
        // therefore, answer[0] = 0
        const int n = nums.size();
        memo = std::vector(1 << n, std::vector<int>(n, -1));
        dfs(1, 0, nums);
        std::vector<int> result;
        generate(result, 1, 0, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> memo;

    int dfs(int state, int prev, const std::vector<int>& nums)
    {
        const int n = nums.size();
        if (state == (1 << n) - 1)
            return std::abs(prev - nums[0]);

        if (memo[state][prev] != -1)
            return memo[state][prev];

        int result = INT_MAX;
        for (int val = 0; val < n; ++val) {
            if ((state >> val) & 1)
                continue;

            result = std::min(result, dfs(state | (1 << val), val, nums) + std::abs(prev - nums[val]));
        }
        return memo[state][prev] = result;
    }

    void generate(std::vector<int>& result, int state, int prev, const std::vector<int>& nums)
    {
        const int n = nums.size();
        result.push_back(prev);
        if (state == (1 << n) - 1)
            return;

        for (int val = 0; val < n; ++val) {
            if ((state >> val) & 1)
                continue;

            if (dfs(state, prev, nums) == dfs(state | (1 << val), val, nums) + std::abs(prev - nums[val])) {
                generate(result, state | (1 << val), val, nums);
                break;
            }
        }
    }
};