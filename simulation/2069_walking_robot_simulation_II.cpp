#include <string>
#include <vector>

/**
 * A width x height grid is on an XY-plane with the bottom-left cell at (0, 0) and the top-right cell at (width - 1,
 * height - 1). The grid is aligned with the four cardinal directions ("North", "East", "South", and "West"). A robot is
 * initially at cell (0, 0) facing direction "East".
 *
 * The robot can be instructed to move for a specific number of steps. For each step, it does the following.
 *
 * 1. Attempts to move forward one cell in the direction it is facing.
 *
 * 2. If the cell the robot is moving to is out of bounds, the robot instead turns 90 degrees counterclockwise and
 * retries the step.
 *
 * After the robot finishes moving the number of steps required, it stops and awaits the next instruction.
 *
 * Implement the Robot class:
 *
 * - Robot(int width, int height) Initializes the width x height grid with the robot at (0, 0) facing "East".
 *
 * - void step(int num) Instructs the robot to move forward num steps.
 *
 * - int[] getPos() Returns the current cell the robot is at, as an array of length 2, [x, y].
 *
 * - String getDir() Returns the current direction of the robot, "North", "East", "South", or "West".
 *
 * ! 2 <= width, height <= 100
 * ! 1 <= num <= 10^5
 * ! At most 10^4 calls in total will be made to step, getPos, and getDir.
 */

class Robot {
public:
    Robot(int width, int height) : w(width - 1), h(height - 1), perimeter(2 * (w + h)) {}

    void step(int num)
    {
        moved = num > 0;
        pos = (pos + num) % perimeter;
    }

    std::vector<int> getPos()
    {
        if (pos <= w)
            return {pos, 0};

        if (pos <= w + h)
            return {w, pos - w};

        if (pos <= 2 * w + h)
            return {w - (pos - (w + h)), h};

        return {0, h - (pos - (2 * w + h))};
    }

    std::string getDir()
    {
        if (!moved)
            return "East";

        if (pos == 0)
            return "South";

        if (pos <= w)
            return "East";

        if (pos <= w + h)
            return "North";

        if (pos <= 2 * w + h)
            return "West";

        return "South";
    }

private:
    bool moved{false};
    int w;
    int h;
    int perimeter;
    int pos{0};
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */