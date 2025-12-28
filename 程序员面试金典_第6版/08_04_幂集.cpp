#include <vector>

/**
 * 幂集。编写一种方法，返回某集合的所有子集。集合中不包含重复的元素。
 *
 * 说明：解集不能包含重复的子集。
 */

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> result;
        std::vector<int> path;
        dfs(result, path, 0, nums);
        return result;
    }

private:
    void dfs(std::vector<std::vector<int>>& result, std::vector<int>& path, int i, const std::vector<int>& nums)
    {
        result.push_back(path);
        if (i == nums.size())
            return;

        for (int j = i; j < nums.size(); ++j) {
            path.push_back(nums[j]);
            dfs(result, path, j + 1, nums);
            path.pop_back();
        }
    }
};