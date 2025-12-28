#include <vector>

/**
 * Given an integer array "nums" of unique elements, return all possible subsets (the power set).
 *
 * A subset of an integer is a selection of elements (possibly none) of the array
 *
 * The solution set, must not contain duplicate subsets. Return the solution in any order.
 *
 * ! 1 <= nums.length <= 10
 * ! -10 <= nums[i] <= 10
 * ! All the numbers of nums are unique.
 */

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> subset;
        backtrack(result, subset, 0, nums);
        return result;
    }

private:
    void backtrack(std::vector<std::vector<int>>& result, std::vector<int>& subset, int i, const std::vector<int>& nums)
    {
        if (i == nums.size()) {
            result.push_back(subset);
            return;
        }
        backtrack(result, subset, i + 1, nums);
        subset.push_back(nums[i]);
        backtrack(result, subset, i + 1, nums);
        subset.pop_back();
    }
};