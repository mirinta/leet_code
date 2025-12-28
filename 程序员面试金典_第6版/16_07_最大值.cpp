/**
 * 编写一个方法，找出两个数字a和b中最大的那一个。不得使用if-else或其他比较运算符。
 */

class Solution {
public:
    int maximum(int a, int b)
    {
        const bool isANegative = (a >> 31) & 1;
        const bool isBNegative = (b >> 31) & 1;
        if (isANegative ^ isBNegative)
            return isANegative ? b : a;

        const int diff = a - b;
        return (diff >> 31) & 1 ? b : a;
    }
};