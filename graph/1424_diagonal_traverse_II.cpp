#include <queue>
#include <unordered_map>
#include <vector>

/**
 * Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the
 * below images.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i].length <= 10^5
 * ! 1 <= sum(nums[i].length) <= 10^5
 * ! 1 <= nums[i][j] <= 10^5
 */

class Solution {
public:
    std::vector<int> findDiagonalOrder(std::vector<std::vector<int>>& nums)
    {
        return approach2(nums);
    }

private:
    // BFS
    std::vector<int> approach2(const std::vector<std::vector<int>>& nums)
    {
        std::vector<int> result;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                result.push_back(nums[x][y]);
                if (y == 0 && x + 1 < nums.size()) {
                    queue.emplace(x + 1, y);
                }
                if (y + 1 < nums[x].size()) {
                    queue.emplace(x, y + 1);
                }
            }
        }
        return result;
    }

    std::vector<int> approach1(const std::vector<std::vector<int>>& nums)
    {
        std::unordered_map<int, std::vector<int>> map;
        for (int i = nums.size() - 1; i >= 0; --i) {
            for (int j = 0; j < nums[i].size(); ++j) {
                map[i + j].push_back(nums[i][j]);
            }
        }
        int group = 0;
        std::vector<int> result;
        while (map.count(group)) {
            for (const auto& val : map[group]) {
                result.push_back(val);
            }
            group++;
        }
        return result;
    }
};