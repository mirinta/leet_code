#include <vector>

/**
 * 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B[i] 的值是数组 A 中除了下标 i
 * 以外的元素的积, 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。
 *
 * 不能使用除法。
 *
 * ! 所有元素乘积之和不会溢出 32 位整数
 * ! a.length <= 100000
 */

class Solution {
public:
    std::vector<int> constructArr(std::vector<int>& a)
    {
        const int n = a.size();
        // prefix = {1, a[0], a[0]*a[1], ...}
        std::vector<int> prefix(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] * a[i - 1];
        }
        // suffix = {..., a[n-2]*a[n-1], a[n-1], 1}
        std::vector<int> suffix(n + 1, 1);
        for (int i = n - 1; i >= 0; --i) {
            suffix[i] = a[i] * suffix[i + 1];
        }
        // [X X X] i [X X X]
        std::vector<int> result(n, 1);
        for (int i = 1; i <= n; ++i) {
            result[i - 1] = prefix[i - 1] * suffix[i];
        }
        return result;
    }
};