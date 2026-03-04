#include <vector>

/**
 * Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.
 *
 * A grid is said to be valid if all the cells above the main diagonal are zeros.
 *
 * Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.
 *
 * The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).
 *
 * ! n == grid.length == grid[i].length
 * ! 1 <= n <= 200
 * ! grid[i][j] is either 0 or 1
 */

class Solution {
public:
    int minSwaps(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<int> zeros(n, 0);
        for (int i = 0; i < n; ++i) {
            int count = 0;
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 1)
                    break;

                count++;
            }
            zeros[i] = count;
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int target = n - i - 1;
            int j = i;
            while (j < n && zeros[j] < target) {
                j++;
            }
            if (j == n)
                return -1;

            result += j - i;
            for (int k = j; k > i; --k) {
                std::swap(zeros[k], zeros[k - 1]);
            }
        }
        return result;
    }
};