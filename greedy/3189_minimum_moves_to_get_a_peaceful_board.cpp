#include <algorithm>
#include <vector>

/**
 * Given a 2D array rooks of length n, where rooks[i] = [xi, yi] indicates the position of a rook on
 * an n x n chess board. Your task is to move the rooks 1 cell at a time vertically or horizontally
 * (to an adjacent cell) such that the board becomes peaceful.
 *
 * A board is peaceful if there is exactly one rook in each row and each column.
 *
 * Return the minimum number of moves required to get a peaceful board.
 *
 * Note that at no point can there be two rooks in the same cell.
 *
 * ! 1 <= n == rooks.length <= 500
 * ! 0 <= xi, yi <= n - 1
 * ! The input is generated such that there are no 2 rooks in the same cell.
 */

class Solution {
public:
    int minMoves(std::vector<std::vector<int>>& rooks)
    {
        const int n = rooks.size();
        std::sort(rooks.begin(), rooks.end(), [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::abs(rooks[i][0] - i);
        }
        std::sort(rooks.begin(), rooks.end(), [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        for (int i = 0; i < n; ++i) {
            result += std::abs(rooks[i][1] - i);
        }
        return result;
    }
};