#include <vector>

/**
 * The n-queens puzzle is the problem of placing "n" queens on an "n x n" chessboard such that no
 * two queens attack each other.
 *
 * Given an integer "n", return the number of distinct solutions to the n-queens puzzle.
 *
 * ! 1 <= n <= 9
 */

class Solution {
public:
    int totalNQueens(int n)
    {
        // 0 for empty, 1 for queen
        std::vector<std::vector<int>> board(n, std::vector<int>(n, 0));
        int result = 0;
        backtrack(result, board, 0);
        return result;
    }

private:
    void backtrack(int& result, std::vector<std::vector<int>>& board, int row)
    {
        if (row == board.size()) {
            result++;
            return;
        }
        for (int col = 0; col < board[row].size(); ++col) {
            if (isValid(row, col, board)) {
                board[row][col] = 1;
                backtrack(result, board, row + 1);
                board[row][col] = 0;
            }
        }
    }

    bool isValid(int row, int col, const std::vector<std::vector<int>>& board)
    {
        // we only need to check the previous rows
        // row-2: ?   ?   ?
        // row-1:   ? ? ?
        //   row:     1
        for (int i = row - 1, offset = 1; i >= 0; --i, ++offset) {
            if (board[i][col] == 1)
                return false;

            if (col - offset >= 0 && board[i][col - offset] == 1)
                return false;

            if (col + offset < board[i].size() && board[i][col + offset] == 1)
                return false;
        }
        return true;
    }
};
