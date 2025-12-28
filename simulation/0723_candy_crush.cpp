#include <unordered_set>
#include <vector>

/**
 * This question is about implementing a basic elimination algorithm for Candy Crush.
 *
 * Given an m x n integer array board representing the grid of candy where board[i][j] represents
 * the type of candy. A value of board[i][j] == 0 represents that the cell is empty.
 *
 * The given board represents the state of the game following the player's move. Now, you need to
 * restore the board to a stable state by crushing candies according to the following rules:
 *
 * - If three or more candies of the same type are adjacent vertically or horizontally, crush them
 * all at the same time - these positions become empty.
 *
 * - After crushing all candies simultaneously, if an empty space on the board has candies on top of
 * itself, then these candies will drop until they hit a candy or bottom at the same time. No new
 * candies will drop outside the top boundary.
 *
 * - After the above steps, there may exist more candies that can be crushed. If so, you need to
 * repeat the above steps.
 *
 * - If there does not exist more candies that can be crushed (i.e., the board is stable), then
 * return the current board.
 *
 * You need to perform the above rules until the board becomes stable, then return the stable board.
 *
 * ! m == board.length
 * ! n == board[i].length
 * ! 3 <= m, n <= 50
 * ! 1 <= board[i][j] <= 2000
 */

class Solution {
public:
    std::vector<std::vector<int>> candyCrush(std::vector<std::vector<int>>& board)
    {
        m = board.size();
        n = board[0].size();
        auto aboutToCrush = find(board);
        while (!aboutToCrush.empty()) {
            crush(board, aboutToCrush);
            drop(board);
            aboutToCrush = find(board);
        }
        return board;
    }

private:
    int m{0};
    int n{0};

    int encode(int i, int j) const
    {
        return i * n + j;
    }

    std::pair<int, int> decode(int val) const
    {
        return {val / n, val % n};
    }

    void drop(std::vector<std::vector<int>>& board) const
    {
        // X
        // X <- i
        // 0
        // 0 <- pos
        for (int j = 0; j < n; ++j) {
            int pos = -1;
            for (int i = m - 1; i >= 0; --i) {
                if (board[i][j] == 0) {
                    pos = std::max(i, pos);
                } else if (pos >= 0) {
                    std::swap(board[pos][j], board[i][j]);
                    pos--;
                }
            }
        }
    }

    void crush(std::vector<std::vector<int>>& board, const std::unordered_set<int>& positions) const
    {
        for (const auto& pos : positions) {
            const auto [i, j] = decode(pos);
            board[i][j] = 0;
        }
    }

    std::unordered_set<int> find(const std::vector<std::vector<int>>& board) const
    {
        std::unordered_set<int> positions;
        // check vertically
        for (int i = 1; i < m - 1; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 0)
                    continue;

                if (board[i][j] == board[i - 1][j] && board[i][j] == board[i + 1][j]) {
                    positions.emplace(encode(i, j));
                    positions.emplace(encode(i + 1, j));
                    positions.emplace(encode(i - 1, j));
                }
            }
        }
        // check horizontally
        for (int i = 0; i < m; ++i) {
            for (int j = 1; j < n - 1; ++j) {
                if (board[i][j] == 0)
                    continue;

                if (board[i][j] == board[i][j - 1] && board[i][j] == board[i][j + 1]) {
                    positions.emplace(encode(i, j));
                    positions.emplace(encode(i, j + 1));
                    positions.emplace(encode(i, j - 1));
                }
            }
        }
        return positions;
    }
};