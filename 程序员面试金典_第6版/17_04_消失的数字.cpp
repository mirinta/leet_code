#include <vector>

/**
 * 数组nums包含从0到n的所有整数，但其中缺了一个。请编写代码找出那个缺失的整数。你有办法在O(n)时间内完成吗？
 *
 * 注意：本题相对书上原题稍作改动
 */

class Solution {
public:
    int missingNumber(std::vector<int>& nums)
    {
        int XOR = 0;
        for (const auto& val : nums) {
            XOR ^= val;
        }
        for (int i = 1; i <= nums.size(); ++i) {
            XOR ^= i;
        }
        return XOR;
    }
};