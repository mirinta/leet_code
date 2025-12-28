/**
 * 写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。
 *
 * ! a, b 均可能是负数或 0
 * ! 结果不会溢出 32 位整数
 */

class Solution {
public:
    int add(int a, int b)
    {
        if (a == 0)
            return b;

        if (b == 0)
            return a;

        int sum = a ^ b;
        int carry = static_cast<unsigned>(a & b) << 1;
        return add(sum, carry);
    }
};