#include <vector>

/**
 * Assume the following rules are for the tic-tac-toe game on an n x n board between two players:
 *
 * - 1. A move is guaranteed to be valid and is placed on an empty block.
 *
 * - 2. Once a winning condition is reached, no more moves are allowed.
 *
 * - 3. A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row
 * wins the game.
 *
 * Implement the TicTacToe class:
 *
 * - TicTacToe(int n) Initializes the object the size of the board n.
 *
 * - int move(int row, int col, int player) Indicates that the player with id player plays at the
 * cell (row, col) of the board. The move is guaranteed to be a valid move, and the two players
 * alternate in making moves. Return
 *
 * - 0 if there is no winner after the move,
 *
 * - 1 if player 1 is the winner after the move, or
 *
 * - 2 if player 2 is the winner after the move.
 */

class TicTacToe {
public:
    TicTacToe(int n) : rows(n, 0), cols(n, 0) {}

    int move(int row, int col, int player)
    {
        const int n = rows.size();
        const int score = player == 1 ? 1 : -1;
        rows[row] += score;
        cols[col] += score;
        if (row == col) {
            diagonal += score;
        }
        if (row + col == n - 1) {
            antidiagonal += score;
        }
        if (std::abs(rows[row]) == n || std::abs(cols[col]) == n || std::abs(diagonal) == n ||
            std::abs(antidiagonal) == n)
            return player;

        return 0;
    }

private:
    std::vector<int> rows; // rows[i] = sum of board[i][...]
    std::vector<int> cols; // cols[i] = sum of board[...][i]
    int diagonal{0};
    int antidiagonal{0};
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
