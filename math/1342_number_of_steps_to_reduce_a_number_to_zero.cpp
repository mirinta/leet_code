/**
 * Given an integer "num", return the number of steps to reduce it to zero.
 *
 * In one step, if the current number is even, you have to divide it by 2, otherwise, you have to
 * subtract 1 from it.
 */

class Solution {
public:
    int numberOfSteps(int num)
    {
        int steps = 0;
        while (num) {
            steps += num % 2 == 0 ? 1 : 2;
            num /= 2;
        } // an extra step when num becomes 1
        steps--;
        return steps < 0 ? 0 : steps;
    }
};