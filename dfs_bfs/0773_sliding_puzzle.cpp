#include <queue>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

/**
 * On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by
 * 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
 *
 * The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
 *
 * Given the puzzle board board, return the least number of moves required so that the state of the
 * board is solved. If it is impossible for the state of the board to be solved, return -1.
 *
 * ! board.length == 2
 * ! board[i].length == 3
 * ! 0 <= board[i][j] <= 5
 * ! Each value board[i][j] is unique.
 */

class Solution {
public:
    int slidingPuzzle(std::vector<std::vector<int>>& board)
    {
        std::string initState;
        int initX = -1;
        int initY = -1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                initState.push_back(board[i][j] + '0');
                if (board[i][j] == 0) {
                    initX = i;
                    initY = j;
                }
            }
        }
        std::queue<std::tuple<int, int, std::string>> queue;
        queue.emplace(initX, initY, initState);
        static const std::string target("123450");
        static const std::vector<std::pair<int, int>> kDirections{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        std::unordered_set<std::string> visited;
        visited.emplace(std::move(initState));
        int moves = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y, state] = queue.front();
                queue.pop();
                if (state == target)
                    return moves;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    auto copy = state;
                    std::swap(copy[encode(x, y)], copy[encode(i, j)]);
                    if (!visited.count(copy)) {
                        visited.insert(copy);
                        queue.emplace(i, j, std::move(copy));
                    }
                }
            }
            moves++;
        }
        return -1;
    }

private:
    static constexpr int m = 2;
    static constexpr int n = 3;

    int encode(int i, int j)
    {
        return i * n + j;
    }
};