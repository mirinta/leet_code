#include <string>
#include <vector>

/**
 * 给定一个mxn二维字符网格board和一个字符串单词word。
 *
 * 如果word存在于网格中，返回true；否则，返回false。
 *
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 *
 * 同一个单元格内的字母不允许被重复使用。
 *
 * ! m == board.length
 * ! n = board[i].length
 * ! 1 <= m, n <= 6
 * ! 1 <= word.length <= 15
 * ! board 和 word 仅由大小写英文字母组成
 *
 * ! 本题与LC 79相同。
 */

class Solution {
public:
    bool exist(std::vector<std::vector<char>>& board, const std::string& word)
    {
        const int m = board.size();
        const int n = board[0].size();
        for (int x = 0; x < m; ++x) {
            for (int y = 0; y < n; ++y) {
                backtrack(x, y, 0, board, word);
                if (found)
                    return true;
            }
        }
        return false;
    }

private:
    bool found = false;

    void backtrack(int x, int y, int i, std::vector<std::vector<char>>& board, const std::string& word)
    {
        if (i == word.size()) {
            found = true;
            return;
        }
        if (found || x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
            return;

        if (board[x][y] != word[i])
            return;

        const char letter = board[x][y];
        board[x][y] = '#'; // mark this character as visited
        backtrack(x - 1, y, i + 1, board, word);
        backtrack(x + 1, y, i + 1, board, word);
        backtrack(x, y - 1, i + 1, board, word);
        backtrack(x, y + 1, i + 1, board, word);
        board[x][y] = letter; // restore
    }
};