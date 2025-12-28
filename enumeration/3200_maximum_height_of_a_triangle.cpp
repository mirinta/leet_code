#include <array>

/**
 * You are given two integers red and blue representing the count of red and blue colored balls. You
 * have to arrange these balls to form a triangle such that the 1st row will have 1 ball, the 2nd
 * row will have 2 balls, the 3rd row will have 3 balls, and so on.
 *
 * All the balls in a particular row should be the same color, and adjacent rows should have
 * different colors.
 *
 * Return the maximum height of the triangle that can be achieved.
 *
 * ! 1 <= red, blue <= 100
 */

class Solution {
public:
    int maxHeightOfTriangle(int red, int blue)
    {
        std::array<int, 2> balls{red, blue};
        return std::max(solve(balls, true), solve(balls, false));
    }

private:
    int solve(std::array<int, 2> balls, bool useRed)
    {
        int height = 0;
        while (balls[useRed] >= height) {
            balls[useRed] -= height;
            useRed = !useRed;
            height++;
        }
        return std::max(0, height - 1);
    }
};
