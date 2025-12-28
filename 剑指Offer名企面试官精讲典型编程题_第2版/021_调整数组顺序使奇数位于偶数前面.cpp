#include <vector>

/**
 * 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。
 *
 * ! 0 <= nums.length <= 50000
 * ! 0 <= nums[i] <= 10000
 */

class Solution {
public:
    std::vector<int> exchange(const std::vector<int>& nums)
    {
        const auto n = nums.size();
        if (n <= 1)
            return nums;

        std::vector<int> result(nums);
        int lo = 0;
        int hi = n - 1;
        while (true) {
            while (lo < n && result[lo] % 2 != 0) {
                lo++;
            }
            while (hi >= 0 && result[hi] % 2 == 0) {
                hi--;
            }
            if (lo >= hi)
                break;

            std::swap(result[hi--], result[lo++]);
        }
        return result;
    }
};