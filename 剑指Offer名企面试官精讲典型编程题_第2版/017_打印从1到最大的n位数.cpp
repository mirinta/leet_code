#include <vector>

/**
 * 输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。
 *
 * 比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。
 *
 * ! n为正整数。
 *
 * 示例：
 * 输入: n = 1
 * 输出: [1,2,3,4,5,6,7,8,9]
 */

class Solution {
public:
    std::vector<int> printNumbers(int n)
    {
        if (n <= 0)
            return {};

        int maxVal = 0;
        while (n) {
            maxVal = 10 * maxVal + 9;
            n--;
        }
        std::vector<int> result;
        for (int i = 1; i <= maxVal; ++i) {
            result.push_back(i);
        }
        return result;
    }
};