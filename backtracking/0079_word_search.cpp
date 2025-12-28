#include <string>
#include <vector>

/**
 * Given an m x n grid of characters "board" and a string "word", return true if "word" exists in
 * the grid.
 *
 * The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are
 * horizontally or vertically neighboring. The same letter cell may not be used more than once.
 *
 * ! m == board.length
 * ! n = board[i].length
 * ! 1 <= m, n <= 6
 * ! 1 <= word.length <= 15
 * ! board and word consists of only lowercase and uppercase English letters.
 */

class Solution {
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word)
    {
        const int m = board.size();
        const int n = board[0].size();
        Vec2D<bool> visited(m, std::vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (backtrack(visited, i, j, 0, word, board))
                    return true;
            }
        }
        return false;
    }

private:
    template<typename T>
    using Vec2D = std::vector<std::vector<T>>;

    bool backtrack(Vec2D<bool>& visited, int x, int y, int index, const std::string& word, const Vec2D<char>& board)
    {
        if (index == word.size())
            return true;

        const int m = board.size();
        const int n = board[0].size();
        if (x < 0 || x >= m || y < 0 || y >= n)
            return false;

        if (visited[x][y] || board[x][y] != word[index])
            return false;

        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        visited[x][y] = true;
        for (const auto& [dx, dy] : kDirections) {
            if (backtrack(visited, x + dx, y + dy, index + 1, word, board))
                return true;
        }
        visited[x][y] = false;
        return false;
    }
};