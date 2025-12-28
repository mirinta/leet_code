#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * 在一个长度为 n 的数组 nums 里的所有数字都在0～n-1
 * 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
 *
 * 示例1：
 * 输入：[2, 3, 1, 0, 2, 5, 3]
 * 输出：2或3
 *
 * ! 2 <= n <= 100000
 */

class Solution {
public:
    // 【问题】若无重复数字，应返回什么？
    // - 这里暂时返回-1，因为题目说元素取值范围是[0, n-1]
    // 【注意】early return，以及检查数组内元素是否有非法取值的情况
    int findRepeatNumber(std::vector<int>& nums)
    {
        return approach3(nums);
    }

private:
    int approach1(std::vector<int>& nums)
    {
        // 方法1：先排序，再比较相邻数字，若相同则返回
        // 时间复杂度O(nlogn)，空间复杂度O(1)
        if (nums.size() < 2)
            return 0;

        std::sort(nums.begin(), nums.end());
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] < 0 || nums[i] >= nums.size())
                break;

            if (nums[i] == nums[i - 1])
                return nums[i];
        }
        return -1;
    }

    int approach2(std::vector<int>& nums)
    {
        // 方法2：HashSet，时间复杂度O(n)，空间复杂度O(n)
        if (nums.size() < 2)
            return 0;

        std::unordered_set<int> set;
        for (const auto& val : nums) {
            if (val < 0 || val >= nums.size())
                break;

            if (set.count(val))
                return val;

            set.emplace(val);
        }
        return -1;
    }

    int approach3(std::vector<int>& nums)
    {
        // 方法3：原地交换，时间复杂度O(n)，空间复杂度O(1)
        // - 共n个数字，数字范围是[0, n-1]，所以对每个遍历到的数字nums[i]：
        // - 1. 若nums[i] = i，说明i在正确的位置上，继续（i++）；
        // - 2. 若nums[i] = j且nums[i] = nums[j]，说明有重复数字，返回nums[i]；
        //      若nums[i] = j且nums[i] != nums[j]，交换i与j位置的两个数组，继续执行步骤2.
        if (nums.size() < 2)
            return 0;

        size_t i = 0;
        while (i < nums.size()) {
            if (nums[i] < 0 || nums[i] >= nums.size())
                break;

            if (nums[i] == i) {
                i++;
                continue;
            }
            if (nums[i] != nums[nums[i]]) {
                std::swap(nums[i], nums[nums[i]]);
            } else {
                return nums[i];
            }
        }
        return -1;
    }
};