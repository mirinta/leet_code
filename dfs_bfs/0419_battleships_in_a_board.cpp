#include <vector>

/**
 * Given an m x n matrix board where each cell is a battleship 'X' or empty '.', return the number
 * of the battleships on board.
 *
 * Battleships can only be placed horizontally or vertically on board. In other words, they can only
 * be made of the shape 1 x k (1 row, k columns) or k x 1 (k rows, 1 column), where k can be of any
 * size. At least one horizontal or vertical cell separates between two battleships (i.e., there are
 * no adjacent battleships).
 *
 * ! m == board.length
 * ! n == board[i].length
 * ! 1 <= m, n <= 200
 * ! board[i][j] is either '.' or 'X'.
 */

class Solution {
public:
    int countBattleships(std::vector<std::vector<char>>& board)
    {
        const int m = board.size();
        const int n = board[0].size();
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X') {
                    dfs(board, i, j);
                    result++;
                }
            }
        }
        return result;
    }

private:
    void dfs(std::vector<std::vector<char>>& board, int i, int j)
    {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return;

        if (board[i][j] != 'X')
            return;

        board[i][j] = '.';
        dfs(board, i + 1, j);
        dfs(board, i - 1, j);
        dfs(board, i, j + 1);
        dfs(board, i, j - 1);
    }
};