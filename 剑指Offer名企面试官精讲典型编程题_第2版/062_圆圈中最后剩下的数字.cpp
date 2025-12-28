
/**
 * 0,1,···,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字（删除后从下一个数字开始计数）。
 *
 * 求出这个圆圈里剩下的最后一个数字。
 *
 * 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
 *
 * ! 1 <= n <= 10^5
 * ! 1 <= m <= 10^6
 */

class Solution {
public:
    int lastRemaining(int n, int m)
    {
        // f(n,m) = (f(n-1,m) + m) % n, where n > 1
        // - if n = 1, f(n, m) = 0
        int last = 0;
        for (int i = 2; i <= n; ++i) {
            last = (last + m) % i;
        }
        return last;
    }
};