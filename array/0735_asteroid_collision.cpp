#include <stack>
#include <vector>

/**
 * We are given an array asteroids of integers representing asteroids in a row.
 *
 * For each asteroid, the absolute value represents its size, and the sign represents its direction
 * (positive meaning right, negative meaning left). Each asteroid moves at the same speed.
 *
 * Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one
 * will explode. If both are the same size, both will explode. Two asteroids moving in the same
 * direction will never meet.
 *
 * ! 2 <= asteroids.length <= 10^4
 * ! -1000 <= asteroids[i] <= 1000
 * ! asteroids[i] != 0
 */

class Solution {
public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids)
    {
        // positive: ->
        // negative: <-
        std::stack<int> stack;
        for (const auto& val : asteroids) {
            bool survived = true;
            while (!stack.empty() && stack.top() > 0 && val < 0) {
                const int sum = stack.top() + val;
                if (sum < 0) {
                    stack.pop();
                    continue;
                }
                if (sum == 0) {
                    stack.pop();
                }
                survived = false;
                break;
            }
            if (survived) {
                stack.push(val);
            }
        }
        std::vector<int> result(stack.size());
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = stack.top();
            stack.pop();
        }
        return result;
    }
};
