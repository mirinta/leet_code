#include <vector>

/**
 * 给定两个排序后的数组 A 和 B，其中 A 的末端有足够的缓冲空间容纳 B。 编写一个方法，将 B 合并入 A
 * 并排序。
 *
 * 初始化 A 和 B 的元素数量分别为 m 和 n。
 *
 * ! A.length == n + m
 */

class Solution {
public:
    void merge(std::vector<int>& A, int m, std::vector<int>& B, int n)
    {
        for (int k = A.size() - 1, i = m - 1, j = n - 1; k >= 0; --k) {
            if (i < 0) {
                A[k] = B[j--];
                continue;
            }
            if (j < 0) {
                A[k] = A[i--];
                continue;
            }
            if (A[i] > B[j]) {
                A[k] = A[i--];
            } else {
                A[k] = B[j--];
            }
        }
    }
};