/**
 * There exists an infinitely large two-dimensional grid of uncolored unit cells. You are given a
 * positive integer n, indicating that you must do the following routine for n minutes:
 *
 * - At the first minute, color any arbitrary unit cell blue.
 *
 * - Every minute thereafter, color blue every uncolored cell that touches a blue cell.
 *
 * Below is a pictorial representation of the state of the grid after minutes 1, 2, and 3.
 *
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    long long coloredCells(int n)
    {
        // 1 + 4x1 + 4x2 + ... + 4x(n-1)
        return 1LL + 2LL * (n - 1) * n;
    }
};
