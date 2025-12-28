#include <algorithm>
#include <string>
#include <vector>

/**
 * 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
 *
 * ! 0 < nums.length <= 100
 * ! 输出结果可能非常大，所以你需要返回一个字符串而不是整数
 * ! 拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0
 */

class Solution {
public:
    std::string minNumber(std::vector<int>& nums)
    {
        std::vector<std::string> strs(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            strs[i] = std::to_string(nums[i]);
        }
        std::sort(strs.begin(), strs.end(),
                  [](const std::string& s1, const std::string& s2) { return s1 + s2 < s2 + s1; });
        std::string result;
        for (const auto& s : strs) {
            result.append(s);
        }
        return result;
    }
};