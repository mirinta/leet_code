#include <set>
#include <unordered_map>
#include <vector>

/**
 * A robot on an infinite XY-plane starts at point (0, 0) facing north. The robot can receive a
 * sequence of these three possible types of commands:
 *
 * - -2: Turn left 90 degrees.
 *
 * - -1: Turn right 90 degrees.
 *
 * - 1 <= k <= 9: Move forward k units, one unit at a time.
 *
 * Some of the grid squares are obstacles. The ith obstacle is at grid point obstacles[i] = (xi,
 * yi). If the robot runs into an obstacle, then it will instead stay in its current location and
 * move on to the next command.
 *
 * Return the maximum Euclidean distance that the robot ever gets from the origin squared (i.e. if
 * the distance is 5, return 25).
 *
 * Note:
 *
 * - North means +Y direction.
 *
 * - East means +X direction.
 *
 * - South means -Y direction.
 *
 * - West means -X direction.
 *
 * - There can be obstacle in [0,0].
 *
 * ! 1 <= commands.length <= 10^4
 * ! commands[i] is either -2, -1, or an integer in the range [1, 9].
 * ! 0 <= obstacles.length <= 10^4
 * ! -3 * 10^4 <= xi, yi <= 3 * 10^4
 * ! The answer is guaranteed to be less than 2^31.
 */

class Solution {
public:
    int robotSim(std::vector<int>& commands, std::vector<std::vector<int>>& obstacles)
    {
        std::unordered_map<int, std::set<int>> mapX;
        std::unordered_map<int, std::set<int>> mapY;
        for (const auto& coord : obstacles) {
            mapX[coord[0]].insert(coord[1]);
            mapY[coord[1]].insert(coord[0]);
        }
        int x = 0;
        int y = 0;
        Direction d = North;
        int result = 0;
        for (const auto& command : commands) {
            if (command == -1) {
                d = static_cast<Direction>((d + 1) % 4);
                continue;
            }
            if (command == -2) {
                d = static_cast<Direction>((d + 3) % 4);
                continue;
            }
            const int currX = x;
            const int currY = y;
            switch (d) {
                case North: {
                    y += command;
                    if (!mapX.count(x))
                        break;

                    auto iter = mapX[x].upper_bound(currY);
                    if (iter == mapX[x].end())
                        break;

                    y = std::max(currY, std::min(y, *iter - 1));
                    break;
                }
                case East: {
                    x += command;
                    if (!mapY.count(y))
                        break;

                    auto iter = mapY[y].upper_bound(currX);
                    if (iter == mapY[y].end())
                        break;

                    x = std::max(currX, std::min(x, *iter - 1));
                    break;
                }
                case South: {
                    y -= command;
                    if (!mapX.count(x))
                        break;

                    auto iter = mapX[x].lower_bound(currY);
                    if (iter == mapX[x].begin())
                        break;

                    iter = std::prev(iter);
                    y = std::min(currY, std::max(y, *iter + 1));
                    break;
                }
                case West: {
                    x -= command;
                    if (!mapY.count(y))
                        break;

                    auto iter = mapY[y].lower_bound(currX);
                    if (iter == mapY[y].begin())
                        break;

                    iter = std::prev(iter);
                    x = std::min(currX, std::max(x, *iter + 1));
                    break;
                }
            }
            result = std::max(result, squaredEuclideanDist(x, y));
        }
        return result;
    }

private:
    enum Direction { North, East, South, West };

    int squaredEuclideanDist(int x, int y)
    {
        return x * x + y * y;
    }
};