#include <vector>

/**
 * Given a positive integer "n", generate an "n x n" "matrix" filled with elements from "1" to "n^2"
 * in spiral order.
 *
 * ! 1 <= n <= 20
 */

class Solution {
public:
    std::vector<std::vector<int>> generateMatrix(int n)
    {
        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        int val = 1;
        int top = 0;
        int bottom = n - 1;
        int left = 0;
        int right = n - 1;
        while (val <= n * n) {
            for (int i = left; i <= right && top <= bottom; ++i) {
                result[top][i] = val++;
            }
            top++;
            for (int i = top; i <= bottom && left <= right; ++i) {
                result[i][right] = val++;
            }
            right--;
            for (int i = right; i >= left && top <= bottom; --i) {
                result[bottom][i] = val++;
            }
            bottom--;
            for (int i = bottom; i >= top && left <= right; --i) {
                result[i][left] = val++;
            }
            left++;
        }
        return result;
    }
};