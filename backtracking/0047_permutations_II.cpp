#include <algorithm>
#include <vector>

/**
 * Given a collection of numbers, "nums", that might contain duplicates, return all possible unique
 * permutations in any order.
 */

class Solution {
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        std::sort(nums.begin(), nums.end()); // arrange repeated values together
        std::vector<int> permutation;
        std::vector<bool> visited(nums.size(), false);
        backtrack(permutation, visited, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& permutation, std::vector<bool>& visited, const std::vector<int>& nums)
    {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (visited[i])
                continue;

            if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1])
                continue;

            visited[i] = true;
            permutation.push_back(nums[i]);
            backtrack(permutation, visited, nums);
            permutation.pop_back();
            visited[i] = false;
        }
    }
};
