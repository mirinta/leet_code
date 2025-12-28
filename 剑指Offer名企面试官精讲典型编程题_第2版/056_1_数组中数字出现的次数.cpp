#include <vector>

/**
 * 一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。
 *
 * 请写程序找出这两个只出现一次的数字。
 *
 * 要求时间复杂度是O(n)，空间复杂度是O(1)。
 *
 * ! 2 <= nums.length <= 10000
 *
 * ! 本题与LC 260相同。
 */

class Solution {
public:
    std::vector<int> singleNumbers(std::vector<int>& nums)
    {
        int x_xor_y = 0;
        for (const auto& val : nums) {
            x_xor_y ^= val;
        }
        //      a = 1010
        //     -a = 0110
        // a&(-a) = 0010
        int flag = x_xor_y & (-x_xor_y);
        int x = 0;
        int y = 0;
        for (const auto& val : nums) {
            if (val & flag) {
                x ^= val;
            } else {
                y ^= val;
            }
        }
        return {x, y};
    }
};