#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given an integer array "nums", return all the different possible non-decreasing subsequences of
 * the given array with at least two elements. You may return the answer in any order.
 */

class Solution {
public:
    std::vector<std::vector<int>> findSubsequences(std::vector<int>& nums)
    {
        if (nums.size() < 1)
            return {};

        std::vector<int> subsequence;
        result.clear();
        backtrack(subsequence, 0, nums);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& subsequence, int start, const std::vector<int>& nums)
    {
        if (subsequence.size() > 1) {
            result.push_back(subsequence);
        }
        if (start == nums.size())
            return;

        std::unordered_set<int> used;
        for (int i = start; i < nums.size(); ++i) {
            if (!subsequence.empty() && nums[i] < subsequence.back())
                continue;

            if (used.count(nums[i]))
                continue;

            used.insert(nums[i]);
            subsequence.push_back(nums[i]);
            backtrack(subsequence, i + 1, nums);
            subsequence.pop_back();
        }
    }
};