#include <string>
#include <vector>

/**
 * On an infinite plane, a robot initially stands at (0, 0) and faces north. Note that:
 *
 * - The north direction is the positive direction of the y-axis.
 *
 * - The south direction is the negative direction of the y-axis.
 *
 * - The east direction is the positive direction of the x-axis.
 *
 * - The west direction is the negative direction of the x-axis.
 *
 * The robot can receive one of three instructions:
 *
 * - "G": go straight 1 unit.
 *
 * - "L": turn 90 degrees to the left (i.e., anti-clockwise direction).
 *
 * - "R": turn 90 degrees to the right (i.e., clockwise direction).
 *
 * - The robot performs the instructions given in order, and repeats them forever.
 *
 * Return true if and only if there exists a circle in the plane such that the robot never leaves
 * the circle.
 *
 * ! instructions[i] is 'G', 'L' or, 'R'.
 */

class Solution {
public:
    bool isRobotBounded(const std::string& instructions)
    {
        // directions
        // - go north, (0, 0) -> (0, 1)
        // - go east, (0, 0) -> (1, 0)
        // - go south, (0, 0) -> (0, -1)
        // - go west, (0, 0) -> (-1, 0)
        const std::vector<std::pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int index = 0;
        int x = 0;
        int y = 0;
        for (const auto& instruction : instructions) {
            switch (instruction) {
                case 'L':
                    index = (index + 3) % 4; // north to west
                    break;
                case 'R':
                    index = (index + 1) % 4; // north to east
                    break;
                case 'G':
                    x += directions[index].first;
                    y += directions[index].second;
                    break;
                default:
                    break;
            }
        }
        return (x == 0 && y == 0) || (index != 0);
    }
};