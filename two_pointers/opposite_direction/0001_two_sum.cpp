#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * Given an array of integers "nums" and an integer "target", return indices of the two numbers such
 * that they add up to "target".
 *
 * You may assume that each input would have exactly one solution, and you may not use the same
 * element twice.
 *
 * You can return the answer in any order.
 *
 * ! 2 <= nums.length <= 10^4
 * ! -10^9 <= nums[i] <= 10^9
 * ! -10^9 <= target <= 10^9
 * ! Only one valid answer exists.
 */

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        return approach2(nums, target);
    }

private:
    // time O(NlogN), space O(N)
    std::vector<int> approach2(const std::vector<int>& nums, int target)
    {
        const int n = nums.size();
        std::vector<std::pair<int, int>> pairs(n); // <val, original index>
        for (int i = 0; i < n; ++i) {
            pairs[i].first = nums[i];
            pairs[i].second = i;
        }
        std::sort(pairs.begin(), pairs.end(), [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        int left = 0;
        int right = n - 1;
        while (left < right) {
            const int sum = pairs[left].first + pairs[right].first;
            if (sum == target)
                return {pairs[left].second, pairs[right].second};

            if (sum > target) {
                right--;
            } else {
                left++;
            }
        }
        return {};
    }

    // time O(N), space O(N)
    std::vector<int> approach1(const std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> map; // value to index
        // the problem guarantees that there is exactly one solution
        // assume target = a + b, then both a and b are in the given array
        for (int i = 0; i < nums.size(); ++i) {
            const int diff = target - nums[i];
            if (map.count(diff))
                return {map[diff], i};

            map[nums[i]] = i;
        }
        return {};
    }
};
