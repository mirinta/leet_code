#include <climits>

/**
 * 整数转换。编写一个函数，确定需要改变几个位才能将整数A转成整数B。
 *
 * ! A，B范围在[-2147483648, 2147483647]之间
 */

class Solution {
public:
    int convertInteger(int A, int B)
    {
        return numOfBinaryOnes(A ^ B);
    }

private:
    int numOfBinaryOnes(int n)
    {
        int result = n < 0 ? 1 : 0;
        n &= INT_MAX;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};