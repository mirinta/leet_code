#include <vector>

/**
 * Given an array nums that represents a permutation of integers from 1 to n. We are going to
 * construct a binary search tree (BST) by inserting the elements of nums in order into an initially
 * empty BST. Find the number of different ways to reorder nums so that the constructed BST is
 * identical to that formed from the original array nums.
 *
 * - For example, given nums = [2,1,3], we will have 2 as the root, 1 as a left child, and 3 as a
 * right child. The array [2,3,1] also yields the same BST but [3,2,1] yields a different BST.
 *
 * Return the number of ways to reorder nums such that the BST formed is identical to the original
 * BST formed from nums.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= nums.length
 * ! All integers in nums are distinct.
 */

class Solution {
public:
    int numOfWays(std::vector<int>& nums)
    {
        return dfs(nums) - 1; // original nums is not taken into account
    }

private:
    static constexpr int kMod = 1e9 + 7;

    long long dfs(const std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return 1;

        std::vector<int> left;
        std::vector<int> right;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < nums[0]) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }
        const long long waysToBuildLeft = dfs(left);
        const long long waysToBuildRight = dfs(right);
        return (waysToBuildLeft * waysToBuildRight) % kMod * combination(nums.size() - 1, left.size()) % kMod;
    }

    long long combination(int m, int n)
    {
        static std::vector<std::vector<long long>> memo(1001, std::vector<long long>(1001, -1));
        if (n == 0 || n == m)
            return 1;

        if (memo[m][n] != -1)
            return memo[m][n];

        if (memo[m][m - n] != -1)
            return memo[m][m - n];

        return memo[m][n] = (combination(m - 1, n) + combination(m - 1, n - 1)) % kMod;
    }
};