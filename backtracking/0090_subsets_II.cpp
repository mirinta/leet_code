#include <algorithm>
#include <vector>

/**
 * Given an integer array "nums" that may contain duplicates, return all possible subsets (the power
 * set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in any order.
 *
 * ! 1 <= nums.length <= 10
 * ! -10 <= nums[i] <= 10
 */

class Solution {
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end()); // arrange duplicates together
        std::vector<int> path;
        backtrack(path, 0, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& path, int i, const std::vector<int>& nums)
    {
        result.push_back(path);
        for (int j = i; j < nums.size(); ++j) {
            if (j - 1 >= i && nums[j] == nums[j - 1])
                continue;

            path.push_back(nums[j]);
            backtrack(path, j + 1, nums);
            path.pop_back();
        }
    }
};
