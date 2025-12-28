#include <stdint.h>

/**
 * 编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1'
 * 的个数（也被称为 汉明重量).）。
 *
 * 提示：
 *
 * - 请注意，在某些语言（如Java）中，没有无符号整数类型。
 * 在这种情况下，输入和输出都将被指定为有符号整数类型，并且不应影响您的实现，因为无论整数是有符号的还是无符号的，其内部的二进制表示形式都是相同的。
 *
 * - 在 Java 中，编译器使用 二进制补码 记法来表示有符号整数。因此，在示例3中，输入表示有符号整数-3。
 *
 * 示例 3：
 * 输入：n = 4294967293 (控制台输入 11111111111111111111111111111101，部分语言中 n = -3）
 * 输出：31
 * 解释：输入的二进制串 11111111111111111111111111111101 中，共有 31 位为 '1'。
 *
 * ! 输入必须是长度为 32 的二进制串 。
 *
 * ! 本题与LC 191相同。
 */

class Solution {
public:
    int hammingWeight(uint32_t n)
    {
        return approach2(n);
    }

private:
    // Approach1: O(logn)
    int approach1(uint32_t n)
    {
        int count = 0;
        while (n) {
            if (n & 1) {
                count++;
            }
            n >>= 1;
        }
        return count;
    }

    // Approach2: O(m), m is the number of '1' bits of n
    int approach2(uint32_t n)
    {
        int count = 0;
        while (n) {
            count++;
            n = n & (n - 1); // eliminate the last '1'
        }
        return count;
    }
};