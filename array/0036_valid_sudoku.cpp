#include <array>
#include <cctype>
#include <unordered_map>
#include <vector>

/**
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according
 * to the following rules:
 *
 * - Each row must contain the digits 1-9 without repetition.
 *
 * - Each column must contain the digits 1-9 without repetition.
 *
 * - Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
 *
 * Note:
 *
 * - A Sudoku board (partially filled) could be valid but is not necessarily solvable.
 *
 * - Only the filled cells need to be validated according to the mentioned rules.
 *
 * ! board.length == 9
 * ! board[i].length == 9
 * ! board[i][j] is a digit 1-9 or '.'.
 */

class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board)
    {
        if (!checkRows(board))
            return false;

        if (!checkColumns(board))
            return false;

        return checkSubBoxes(board);
    }

private:
    bool checkRows(const std::vector<std::vector<char>>& board)
    {
        std::array<int, 10> count{};
        for (const auto& row : board) {
            std::fill(count.begin(), count.end(), 0);
            for (const auto& c : row) {
                if (!std::isdigit(c))
                    continue;

                if (++count[c - '0'] > 1)
                    return false;
            }
        }
        return true;
    }

    bool checkColumns(const std::vector<std::vector<char>>& board)
    {
        std::array<int, 10> count{};
        for (int j = 0; j < 9; ++j) {
            std::fill(count.begin(), count.end(), 0);
            for (int i = 0; i < 9; ++i) {
                if (!std::isdigit(board[i][j]))
                    continue;

                if (++count[board[i][j] - '0'] > 1)
                    return false;
            }
        }
        return true;
    }

    bool checkSubBoxes(const std::vector<std::vector<char>>& board)
    {
        std::unordered_map<int, std::array<int, 10>> map;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (!std::isdigit(board[i][j]))
                    continue;

                const int subBoxID = i / 3 * 3 + j / 3;
                if (++map[subBoxID][board[i][j] - '0'] > 1)
                    return false;
            }
        }
        return true;
    }
};