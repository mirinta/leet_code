#include <string>
#include <vector>

/**
 * Tic-tac-toe is played by two players A and B on a 3 x 3 grid. The rules of Tic-Tac-Toe are:
 *
 * - Players take turns placing characters into empty squares ' '.
 *
 * - The first player A always places 'X' characters, while the second player B always places 'O'
 * characters.
 *
 * - 'X' and 'O' characters are always placed into empty squares, never on filled ones.
 *
 * - The game ends when there are three of the same (non-empty) character filling any row, column,
 * or diagonal.
 *
 * - The game also ends if all squares are non-empty.
 *
 * - No more moves can be played if the game is over.
 *
 * Given a 2D integer array moves where moves[i] = [row_i, col_i] indicates that the ith move will
 * be played on grid[row_i][col_i]. return the winner of the game if it exists (A or B). In case the
 * game ends in a draw return "Draw". If there are still movements to play return "Pending".
 *
 * You can assume that moves is valid (i.e., it follows the rules of Tic-Tac-Toe), the grid is
 * initially empty, and A will play first.
 *
 * ! moves[i].length == 2
 * ! 0 <= rowi, coli <= 2
 * ! There are no repeated elements on moves.
 * ! moves follow the rules of tic tac toe.
 */

class Solution {
public:
    std::string tictactoe(std::vector<std::vector<int>>& moves)
    {
        // A plays first
        // - if A wins, min steps = 5 (A3 + B2)
        // - if B wins, min steps = 6 (A3 + B3)
        constexpr auto n = 3;
        if (moves.size() < 2 * n - 1)
            return "Pending";

        std::vector<int> rowFreq(n);
        std::vector<int> colFreq(n);
        int diagonal = 0;
        int antiDiagonal = 0;
        int player = 1; // 1 for A, -1 for B
        for (const auto& move : moves) {
            const auto& row = move[0];
            const auto& col = move[1];
            rowFreq[row] += player;
            colFreq[col] += player;
            if (row == col) {
                diagonal += player;
            }
            if (row + col == n - 1) {
                antiDiagonal += player;
            }
            if (std::abs(rowFreq[row]) == n || std::abs(colFreq[col]) == n || std::abs(diagonal) == n ||
                std::abs(antiDiagonal) == n)
                return player == 1 ? "A" : "B";

            player *= -1;
        }
        return moves.size() == n * n ? "Draw" : "Pending";
    }
};