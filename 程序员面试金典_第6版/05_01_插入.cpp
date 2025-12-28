/**
 * 给定两个整型数字 N 与 M，以及表示比特位置的 i 与 j（i <= j，且从 0 位开始计算）。
 *
 * 编写一种方法，使 M 对应的二进制数字插入 N 对应的二进制数字的第 i ~ j 位区域，不足之处用 0 补齐。
 *
 * 题目保证从 i 位到 j 位足以容纳 M， 例如： M = 10011，则 i～j 区域至少可容纳 5 位。
 */

class Solution {
public:
    int insertBits(int N, int M, int i, int j)
    {
        const int tail = ((1 << i) - 1) & N;
        N >>= j;
        if (N & 1) {
            N -= 1;
        }
        N <<= j;
        N |= tail;
        return N | (M << i);
    }
};