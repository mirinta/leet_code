#include <queue>
#include <vector>

/**
 * There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The
 * ball can go through the empty spaces by rolling up, down, left or right, but it won't stop
 * rolling until hitting a wall. When the ball stops, it could choose the next direction.
 *
 * Given the m x n maze, the ball's start position and the destination, where start = [start_row,
 * start_col] and destination = [destination_row, destination_col], return true if the ball can stop
 * at the destination, otherwise return false.
 *
 * You may assume that the borders of the maze are all walls.
 *
 * ! m == maze.length
 * ! n == maze[i].length
 * ! 1 <= m, n <= 100
 * ! maze[i][j] is 0 or 1.
 * ! start.length == 2
 * ! destination.length == 2
 * ! 0 <= start_row, destination_row <= m
 * ! 0 <= start_col, destination_col <= n
 * ! Both the ball and the destination exist in an empty space, and they will not be in the same
 * ! position initially.
 * ! The maze contains at least 2 empty spaces.
 */

class Solution {
public:
    bool hasPath(std::vector<std::vector<int>>& maze, std::vector<int>& start, std::vector<int>& destination)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        const int m = maze.size();
        const int n = maze[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[start[0]][start[1]] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(start[0], start[1]);
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (x == destination[0] && y == destination[1])
                    return true;

                for (const auto& [dx, dy] : kDirections) {
                    int i = x + dx;
                    int j = y + dy;
                    while (i >= 0 && i < m && j >= 0 && j < n && maze[i][j] != 1) {
                        i += dx;
                        j += dy;
                    }
                    i -= dx;
                    j -= dy;
                    if (!visited[i][j] && maze[i][j] == 0) {
                        visited[i][j] = true;
                        queue.emplace(i, j);
                    }
                }
            }
        }
        return false;
    }
};