#include <vector>

/**
 * Given an array "nums" of distinct integers, return all the possible permutations. You can return
 * the answer in any order.
 *
 * ! 1 <= nums.length <= 6
 * ! -10 <= nums[i] <= 10
 * ! All the integers of nums are unique.
 */

class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums)
    {
        std::vector<bool> used(nums.size(), false);
        std::vector<int> perm;
        std::vector<std::vector<int>> result;
        backtrack(result, perm, used, 0, nums);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result,
                   std::vector<int>& perm,
                   std::vector<bool>& used,
                   int i,
                   const std::vector<int>& nums)
    {
        if (i == nums.size()) {
            result.push_back(perm);
            return;
        }
        for (int j = 0; j < nums.size(); ++j) {
            if (used[j])
                continue;

            used[j] = true;
            perm.push_back(nums[j]);
            backtrack(result, perm, used, i + 1, nums);
            used[j] = false;
            perm.pop_back();
        }
    }
};
