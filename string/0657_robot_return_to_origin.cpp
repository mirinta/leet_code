#include <string>

/**
 * There is a robot starting at the position (0, 0), the origin, on a 2D plane. Given a sequence of
 * its moves, judge if this robot ends up at (0, 0) after it completes its moves.
 *
 * You are given a string "moves" that represents the move sequence of the robot where moves[i]
 * represents its ith move. Valid moves are 'R' (right), 'L' (left), 'U' (up), and 'D' (down).
 *
 * Return true if the robot returns to the origin after if finishes all of its moves, or false
 * otherwise.
 *
 * Note: the way that the robot is "facing" is irrelevant. 'R' will always make the robot move to
 * the right once, 'L' will always make it move left, etc. Also, assume that the magnitude of the
 * robot's movement is the same for each move.
 *
 * ! moves only contains the characters 'U', 'D', 'L' and 'R'.
 */

class Solution {
public:
    bool judgeCircle(const std::string& moves)
    {
        if (moves.empty())
            return true;

        int horizontalMovement = 0;
        int verticalMovement = 0;
        for (const auto& move : moves) {
            switch (move) {
                case 'U':
                    horizontalMovement++;
                    break;
                case 'D':
                    horizontalMovement--;
                    break;
                case 'L':
                    verticalMovement++;
                    break;
                case 'R':
                    verticalMovement--;
                    break;
                default:
                    break;
            }
        }
        return horizontalMovement == 0 && verticalMovement == 0;
    }
};