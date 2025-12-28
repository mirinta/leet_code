#include <queue>
#include <vector>

/**
 * Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the
 * kth smallest element in the matrix.
 *
 * Note that it is the kth smallest element in the sorted order, not the kth distinct element.
 *
 * You must find a solution with a memory complexity better than O(n2).
 *
 * ! n == matrix.length == matrix[i].length
 * ! 1 <= n <= 300
 * ! -10^9 <= matrix[i][j] <= 10^9
 * ! All the rows and columns of matrix are guaranteed to be sorted in non-decreasing order.
 * ! 1 <= k <= n^2
 */

class Solution {
public:
    int kthSmallest(std::vector<std::vector<int>>& matrix, int k)
    {
        return approach2(matrix, k);
    }

private:
    int approach2(const std::vector<std::vector<int>>& matrix, int k)
    {
        const int n = matrix.size();
        int lo = matrix[0][0];
        int hi = matrix[n - 1][n - 1];
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (countSmallerOrEqual(mid, matrix) >= k) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return hi;
    }

    int countSmallerOrEqual(int val, const std::vector<std::vector<int>>& matrix)
    {
        const int n = matrix.size();
        int i = 0;
        int j = n - 1;
        int count = 0;
        while (i < n && j >= 0) {
            if (matrix[i][j] > val) {
                j--;
            } else {
                count += j + 1;
                i++;
            }
        }
        return count;
    }

    int approach1(const std::vector<std::vector<int>>& matrix, int k)
    {
        const int n = matrix.size();
        using Tuple = std::tuple<int, int, int>; // <val, i, j>
        auto comparator = [](const auto& t1, const auto& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator);
        for (int i = 0; i < n; ++i) {
            pq.emplace(matrix[i][0], i, 0);
        }
        int result = -1;
        while (!pq.empty() && k > 0) {
            k--;
            const auto [val, i, j] = pq.top();
            pq.pop();
            result = val;
            if (j + 1 < n) {
                pq.emplace(matrix[i][j + 1], i, j + 1);
            }
        }
        return result;
    }
};