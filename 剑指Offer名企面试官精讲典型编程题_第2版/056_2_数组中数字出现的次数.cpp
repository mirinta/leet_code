#include <vector>

/**
 * 在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。
 *
 * ! 1 <= nums.length <= 10000
 * ! 1 <= nums[i] < 2^31
 */

class Solution {
public:
    int singleNumber(std::vector<int>& nums)
    {
        constexpr int kBitsOfInt = CHAR_BIT * sizeof(int);
        // 2: 0010
        // 2: 0010
        // 2: 0010
        // 3: 0011
        int result = 0;
        for (int i = 0; i < kBitsOfInt; ++i) {
            int count = 0;
            for (const auto& val : nums) {
                count += (val >> i) & 1;
            }
            result += (count % 3) << i;
        }
        return result;
    }
};