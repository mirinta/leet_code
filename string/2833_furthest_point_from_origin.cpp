#include <string>

/**
 * You are given a string moves of length n consisting only of characters 'L', 'R', and '_'. The string represents your
 * movement on a number line starting from the origin 0.
 *
 * In the ith move, you can choose one of the following directions:
 *
 * - move to the left if moves[i] = 'L' or moves[i] = '_'
 *
 * - move to the right if moves[i] = 'R' or moves[i] = '_'
 *
 * Return the distance from the origin of the furthest point you can get to after n moves.
 *
 * ! 1 <= moves.length == n <= 50
 * ! moves consists only of characters 'L', 'R' and '_'.
 */

class Solution {
public:
    int furthestDistanceFromOrigin(std::string& moves)
    {
        int delta = 0;
        int line = 0;
        for (const auto& c : moves) {
            if (c == 'L') {
                delta++;
            } else if (c == 'R') {
                delta--;
            } else {
                line++;
            }
        }
        return std::abs(delta) + line;
    }
};