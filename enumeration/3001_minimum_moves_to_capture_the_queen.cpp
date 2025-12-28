#include <algorithm>

/**
 * There is a 1-indexed 8 x 8 chessboard containing 3 pieces.
 *
 * You are given 6 integers a, b, c, d, e, and f where:
 *
 * - (a, b) denotes the position of the white rook.
 *
 * - (c, d) denotes the position of the white bishop.
 *
 * - (e, f) denotes the position of the black queen.
 *
 * Given that you can only move the white pieces, return the minimum number of moves required to
 * capture the black queen.
 *
 * Note that:
 *
 * Rooks can move any number of squares either vertically or horizontally, but cannot jump over
 * other pieces. Bishops can move any number of squares diagonally, but cannot jump over other
 * pieces. A rook or a bishop can capture the queen if it is located in a square that they can move
 * to. The queen does not move.
 *
 * ! 1 <= a, b, c, d, e, f <= 8
 * ! No two pieces are on the same square.
 */

class Solution {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f)
    {
        // Rook(a, b), Bishop(c, d), Queen(e, f)
        // case 1: Rook and Queen are in the same row, and Bishop is not between them
        if (a == e && (c != a || !inRange(d, std::min(b, f), std::max(b, f))))
            return 1;

        // case 2: Rook and Queen are in the same column, and Bishop is not between them
        if (b == f && (d != b || !inRange(c, std::min(a, e), std::max(a, e))))
            return 1;

        // case 3: Bishop and Queen are not on the same line
        if (std::abs(e - c) != std::abs(d - f))
            return 2;

        // case 4: Bishop and Queen are on the same line, and Rook is between them
        if (std::abs(a - c) == std::abs(b - d) && inRange(a, std::min(c, e), std::max(c, e)) &&
            inRange(b, std::min(d, f), std::max(d, f)))
            return 2;

        return 1;
    }

private:
    bool inRange(int val, int low, int hi)
    {
        return val >= low && val <= hi;
    }
};