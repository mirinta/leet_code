/**
 * 递归乘法。 写一个递归函数，不使用 * 运算符，
 * 实现两个正整数的相乘。可以使用加号、减号、位移，但要吝啬一些。
 *
 * ! 保证乘法范围不会溢出
 */

class Solution {
public:
    int multiply(int A, int B)
    {
        if (A > B)
            return multiply(B, A);

        if (A == 0)
            return 0;

        if (A == 1)
            return B;

        int result = multiply(A >> 1, B) << 1;
        if (A & 1) {
            result += B;
        }
        return result;
    }
};