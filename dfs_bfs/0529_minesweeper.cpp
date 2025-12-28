#include <vector>

/**
 * Let's play the minesweeper game (Wikipedia, online game)!
 *
 * You are given an m x n char matrix board representing the game board where:
 *
 * - 'M' represents an unrevealed mine,
 *
 * - 'E' represents an unrevealed empty square,
 *
 * - 'B' represents a revealed blank square that has no adjacent mines (i.e., above, below, left,
 * right, and all 4 diagonals),
 *
 * - digit ('1' to '8') represents how many mines are adjacent to this revealed square, and
 *
 * - 'X' represents a revealed mine.
 *
 * You are also given an integer array click where click = [clickr, clickc] represents the next
 * click position among all the unrevealed squares ('M' or 'E').
 *
 * Return the board after revealing this position according to the following rules:
 *
 * 1. If a mine 'M' is revealed, then the game is over. You should change it to 'X'.
 *
 * 2. If an empty square 'E' with no adjacent mines is revealed, then change it to a revealed blank
 * 'B' and all of its adjacent unrevealed squares should be revealed recursively.
 *
 * 3. If an empty square 'E' with at least one adjacent mine is revealed, then change it to a digit
 * ('1' to '8') representing the number of adjacent mines.
 *
 * 4. Return the board when no more squares will be revealed.
 *
 * ! m == board.length
 * ! n == board[i].length
 * ! 1 <= m, n <= 50
 * ! board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
 * ! click.length == 2
 * ! 0 <= clickr < m
 * ! 0 <= clickc < n
 * ! board[clickr][clickc] is either 'M' or 'E'.
 */

class Solution {
public:
    std::vector<std::vector<char>> updateBoard(std::vector<std::vector<char>>& board, std::vector<int>& click)
    {
        for (const auto& coordinates : click) {
            const int x = click[0];
            const int y = click[1];
            if (board[x][y] == 'M') {
                board[x][y] = 'X';
                break;
            }
            if (board[x][y] == 'E') {
                dfs(board, x, y);
            }
        }
        return board;
    }

private:
    static const std::vector<int> kOffsets;

    void dfs(std::vector<std::vector<char>>& board, int x, int y)
    {
        const int m = board.size();
        const int n = board[0].size();
        int count = 0;
        for (const auto& dx : kOffsets) {
            for (const auto& dy : kOffsets) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                count += board[i][j] == 'M';
            }
        }
        if (count > 0) {
            board[x][y] = count + '0';
            return;
        }
        board[x][y] = 'B';
        for (const auto& dx : kOffsets) {
            for (const auto& dy : kOffsets) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                if (board[i][j] == 'E') {
                    dfs(board, i, j);
                }
            }
        }
    }
};

const std::vector<int> Solution::kOffsets{-1, 0, 1};