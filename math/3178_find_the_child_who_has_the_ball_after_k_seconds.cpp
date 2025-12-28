/**
 * You are given two positive integers n and k. There are n children numbered from 0 to n - 1
 * standing in a queue in order from left to right.
 *
 * Initially, child 0 holds a ball and the direction of passing the ball is towards the right
 * direction. After each second, the child holding the ball passes it to the child next to them.
 * Once the ball reaches either end of the line, i.e. child 0 or child n - 1, the direction of
 * passing is reversed.
 *
 * Return the number of the child who receives the ball after k seconds.
 *
 * ! 2 <= n <= 50
 * ! 1 <= k <= 50
 */

class Solution {
public:
    int numberOfChild(int n, int k)
    {
        return approach2(n, k);
    }

private:
    // math, TC = O(1), SC = O(1)
    int approach2(int n, int k)
    {
        // from index 0 to index n-1, time = n-1 seconds
        // from index n-1 to index 0, time = n-1 seconds
        const int count = k / (n - 1);
        const int remainder = k % (n - 1);
        return count % 2 ? n - 1 - remainder : remainder;
    }

    // simulation, TC = O(k), SC = O(1)
    int approach1(int n, int k)
    {
        int direction = 1;
        int result = 0;
        while (k) {
            result += direction;
            if (result == n - 1 || result == 0) {
                direction *= -1;
            }
            k--;
        }
        return result;
    }
};