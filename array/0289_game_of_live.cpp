#include <vector>

/**
 * According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular
 * automaton devised by the British mathematician John Horton Conway in 1970."
 *
 * The board is made up of an m x n grid of cells, where each cell has an initial state: live
 * (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors
 * (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia
 * article):
 *
 * 1. Any live cell with fewer than two live neighbors dies as if caused by under-population.
 *
 * 2. Any live cell with two or three live neighbors lives on to the next generation.
 *
 * 3. Any live cell with more than three live neighbors dies, as if by over-population.
 *
 * 4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 *
 * The next state is created by applying the above rules simultaneously to every cell in the current
 * state, where births and deaths occur simultaneously. Given the current state of the m x n grid
 * board, return the next state.
 *
 * ! m == board.length
 * ! n == board[i].length
 * ! 1 <= m, n <= 25
 * ! board[i][j] is 0 or 1.
 */

class Solution {
public:
    // Two-pass, time O(MN), space O(1)
    void gameOfLife(std::vector<std::vector<int>>& board)
    {
        if (board.empty())
            return;

        const int m = board.size();
        const int n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                switch (board[i][j]) {
                    case Die:
                        board[i][j] = countLiveNeighbors(i, j, board) == 3 ? AboutToLive : Die;
                        break;
                    case Live: {
                        const int count = countLiveNeighbors(i, j, board);
                        board[i][j] = count < 2 || count > 3 ? AboutToDie : Live;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                switch (board[i][j]) {
                    case AboutToDie:
                        board[i][j] = Die;
                        break;
                    case AboutToLive:
                        board[i][j] = Live;
                        break;
                    default:
                        break;
                }
            }
        }
    }

private:
    // AboutToDie means the previous state of the cell is Live.
    // AboutToLive means the previous state of the cell is Die.
    enum Status { Die, Live, AboutToDie, AboutToLive };
    const std::vector<std::pair<int, int>> kDirections{{1, 0},   {-1, 0}, {0, 1},  {0, -1},
                                                       {-1, -1}, {1, 1},  {-1, 1}, {1, -1}};

    int countLiveNeighbors(int x, int y, const std::vector<std::vector<int>>& board)
    {
        const int m = board.size();
        const int n = board[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n)
            return 0;

        int count = 0;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= m || j < 0 || j >= n)
                continue;

            if (board[i][j] == Live || board[i][j] == AboutToDie) {
                count++;
            }
        }
        return count;
    }
};