#include <queue>
#include <vector>

/**
 * You are given an n x n integer matrix board where the cells are labeled from 1 to n2 in a
 * Boustrophedon style starting from the bottom left of the board (i.e. board[n - 1][0]) and
 * alternating direction each row.
 *
 * You start on square 1 of the board. In each move, starting from square curr, do the following:
 *
 * - Choose a destination square next with a label in the range [curr + 1, min(curr + 6, n2)]. This
 * choice simulates the result of a standard 6-sided die roll: i.e., there are always at most 6
 * destinations, regardless of the size of the board.
 *
 * - If next has a snake or ladder, you must move to the destination of that snake or ladder.
 * Otherwise, you move to next.
 *
 * - The game ends when you reach the square n2.
 *
 * A board square on row r and column c has a snake or ladder if board[r][c] != -1. The destination
 * of that snake or ladder is board[r][c]. Squares 1 and n2 do not have a snake or ladder.
 *
 * Note that you only take a snake or ladder at most once per move. If the destination to a snake or
 * ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.
 *
 * - For example, suppose the board is [[-1,4],[-1,3]], and on the first move, your destination
 * square is 2. You follow the ladder to square 3, but do not follow the subsequent ladder to 4.
 *
 * Return the least number of moves required to reach the square n2. If it is not possible to reach
 * the square, return -1.
 *
 * ! n == board.length == board[i].length
 * ! 2 <= n <= 20
 * ! board[i][j] is either -1 or in the range [1, n2].
 * ! The squares labeled 1 and n2 do not have any ladders or snakes.
 */

class Solution {
public:
    // BFS, time O(N^2), space O(N^2)
    int snakesAndLadders(std::vector<std::vector<int>>& board)
    {
        const int n = board.size();
        const int nSquare = n * n;
        std::vector<bool> visited(1 + nSquare, false);
        visited[1] = true;
        std::queue<int> queue; // square id
        queue.push(1);
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto current = queue.front();
                queue.pop();
                if (current == nSquare)
                    return steps;

                for (int next = current + 1; next <= std::min(current + 6, nSquare); ++next) {
                    const auto [x, y] = toCoordinates(next, n);
                    if (board[x][y] != -1 && !visited[board[x][y]]) {
                        visited[board[x][y]] = true;
                        queue.push(board[x][y]);
                    } else if (board[x][y] == -1 && !visited[next]) {
                        visited[next] = true;
                        queue.push(next);
                    }
                }
            }
            ++steps;
        }
        return -1;
    }

private:
    std::pair<int, int> toCoordinates(int val, int dimension)
    {
        const int row = dimension - (val - 1) / dimension - 1;
        const int col = (val - 1) % dimension;
        if (row % 2 == dimension % 2)
            return {row, dimension - 1 - col};

        return {row, col};
    }
};
