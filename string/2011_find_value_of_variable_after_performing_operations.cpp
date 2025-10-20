#include <string>
#include <vector>

/**
 * There is a programming language with only four operations and one variable X:
 *
 * ++X and X++ increments the value of the variable X by 1.
 *
 * --X and X-- decrements the value of the variable X by 1.
 *
 * Initially, the value of X is 0.
 *
 * Given an array of strings operations containing a list of operations, return the final value of X
 * after performing all the operations.
 *
 * ! 1 <= operations.length <= 100
 * ! operations[i] will be either "++X", "X++", "--X", or "X--".
 */

class Solution
{
public:
    int finalValueAfterOperations(std::vector<std::string>& operations)
    {
        int result = 0;
        for (const auto& s : operations) {
            if (s.front() == '+' or s.back() == '+') {
                result++;
            } else {
                result--;
            }
        }
        return result;
    }
};