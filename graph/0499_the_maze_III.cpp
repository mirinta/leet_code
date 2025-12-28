#include <queue>
#include <string>
#include <vector>

/**
 * There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The
 * ball can go through the empty spaces by rolling up, down, left or right, but it won't stop
 * rolling until hitting a wall. When the ball stops, it could choose the next direction. There is
 * also a hole in this maze. The ball will drop into the hole if it rolls onto the hole.
 *
 * Given the m x n maze, the ball's position ball and the hole's position hole, where ball =
 * [ball_row, ball_col] and hole = [hole_row, hole_col], return a string instructions of all the
 * instructions that the ball should follow to drop in the hole with the shortest distance possible.
 * If there are multiple valid instructions, return the lexicographically minimum one. If the ball
 * can't drop in the hole, return "impossible".
 *
 * If there is a way for the ball to drop in the hole, the answer instructions should contain the
 * characters 'u' (i.e., up), 'd' (i.e., down), 'l' (i.e., left), and 'r' (i.e., right).
 *
 * The distance is the number of empty spaces traveled by the ball from the start position
 * (excluded) to the destination (included).
 *
 * You may assume that the borders of the maze are all walls (see examples).
 *
 * ! m == maze.length
 * ! n == maze[i].length
 * ! 1 <= m, n <= 100
 * ! maze[i][j] is 0 or 1.
 * ! ball.length == 2
 * ! hole.length == 2
 * ! 0 <= ball_row, hole_row <= m
 * ! 0 <= ball_col, hole_col <= n
 * ! Both the ball and the hole exist in an empty space, and they will not be in the same position
 * ! initially.
 * ! The maze contains at least 2 empty spaces.
 */

class Solution {
public:
    // Dijkstra, time O(MNlog(MN)), space O(MN)
    std::string findShortestWay(std::vector<std::vector<int>>& maze, std::vector<int>& ball, std::vector<int>& hole)
    {
        const int m = maze.size();
        const int n = maze[0].size();
        std::vector<std::vector<int>> distTo(m, std::vector<int>(n, INT_MAX));
        distTo[ball[0]][ball[1]] = 0;
        auto comparator = [](const auto& t1, const auto& t2) {
            const auto& [dist1, x1, y1, instruction1] = t1;
            const auto& [dist2, x2, y2, instruction2] = t2;
            return dist1 == dist2 ? instruction1 > instruction2 : dist1 > dist2;
        };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator); // min heap
        pq.emplace(0, ball[0], ball[1], "");
        while (!pq.empty()) {
            const auto [dist, x, y, instruction] = pq.top();
            pq.pop();
            if (x == hole[0] && y == hole[1])
                return instruction;

            for (const auto& [dx, dy, direction] : kDirections) {
                int i = x + dx;
                int j = y + dy;
                int count = 0;
                while (i >= 0 && i < m && j >= 0 && j < n && maze[i][j] == 0) {
                    count++;
                    if (i == hole[0] && j == hole[1])
                        break;

                    i += dx;
                    j += dy;
                }
                if (count == 0)
                    continue;

                if (i < 0 || i >= m || j < 0 || j >= n || maze[i][j] == 1) {
                    i -= dx;
                    j -= dy;
                }
                if (distTo[i][j] >= dist + count) {
                    distTo[i][j] = dist + count;
                    pq.emplace(distTo[i][j], i, j, instruction + direction);
                }
            }
        }
        return "impossible";
    }

private:
    using Tuple = std::tuple<int, int, int, std::string>; // <dist, x, y, instruction>
    const std::vector<std::tuple<int, int, std::string>> kDirections{{-1, 0, "u"},
                                                                     {1, 0, "d"},
                                                                     {0, -1, "l"},
                                                                     {0, 1, "r"}};
};
