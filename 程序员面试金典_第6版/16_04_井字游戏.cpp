#include <string>
#include <vector>

/**
 * 设计一个算法，判断玩家是否赢了井字游戏。
 * 输入是一个 N x N 的数组棋盘，由字符" "，"X"和"O"组成，其中字符" "代表一个空位。
 *
 * 以下是井字游戏的规则：
 *
 * - 玩家轮流将字符放入空位（" "）中。
 * - 第一个玩家总是放字符"O"，且第二个玩家总是放字符"X"。
 * - "X"和"O"只允许放置在空位中，不允许对已放有字符的位置进行填充。
 * - 当有N个相同（且非空）的字符填充任何行、列或对角线时，游戏结束，对应该字符的玩家获胜。
 * - 当所有位置非空时，也算为游戏结束。
 * - 如果游戏结束，玩家不允许再放置字符。
 *
 * 如果游戏存在获胜者，就返回该游戏的获胜者使用的字符（"X"或"O"）；如果游戏以平局结束，则返回
 * "Draw"；如果仍会有行动（游戏未结束），则返回 "Pending"。
 *
 * ! 1 <= board.length == board[i].length <= 100
 * ! 输入一定遵循井字棋规则
 */

class Solution {
public:
    std::string tictactoe(std::vector<std::string>& board)
    {
        bool hasSpace = false;
        if (check(hasSpace, board, 'O'))
            return "O";

        if (check(hasSpace, board, 'X'))
            return "X";

        return hasSpace ? "Pending" : "Draw";
    }

private:
    bool check(bool& hasSpace, const std::vector<std::string>& board, char target)
    {
        const int n = board.size();
        for (int i = 0; i < n; ++i) {
            int count = 0;
            for (int j = 0; j < n; ++j) {
                count += board[i][j] == target;
                hasSpace |= board[i][j] == ' ';
            }
            if (count == n)
                return true;
        }
        for (int j = 0; j < n; ++j) {
            int count = 0;
            for (int i = 0; i < n; ++i) {
                count += board[i][j] == target;
            }
            if (count == n)
                return true;
        }
        int diagonal = 0;
        int antiDiagonal = 0;
        for (int i = 0; i < n; ++i) {
            diagonal += board[i][i] == target;
            antiDiagonal += board[i][n - i - 1] == target;
        }
        if (diagonal == n || antiDiagonal == n)
            return true;

        return false;
    }
};