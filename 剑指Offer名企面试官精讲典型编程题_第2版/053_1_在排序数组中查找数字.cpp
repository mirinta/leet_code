#include <vector>

/**
 * 统计一个数字在排序数组中出现的次数。
 *
 * ! 0 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 * ! nums 是一个非递减数组
 * ! -10^9 <= target <= 10^9
 *
 * ! 本题与LC 34仅返回值不同。
 */

class Solution {
public:
    int search(std::vector<int>& nums, int target)
    {
        if (nums.empty())
            return 0;

        const int first = findFirst(nums, target);
        if (first < 0)
            return 0;

        const int last = findLast(nums, target);
        return last - first + 1;
    }

private:
    int findFirst(const std::vector<int>& nums, int target)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo == nums.size() || nums[lo] != target ? -1 : lo;
    }

    int findLast(const std::vector<int>& nums, int target)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (nums[mid] <= target) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi < 0 || nums[hi] != target ? -1 : hi;
    }
};