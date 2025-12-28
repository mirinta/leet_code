#include <stack>
#include <string>
#include <vector>

/**
 * You are keeping the scores for a baseball game with strange rules. At the beginning of the game,
 * you start with an empty record.
 *
 * You are given a list of strings "operations", where operations[i] is the ith operation you must
 * apply to the record and is one of the following:
 *
 * - An integer x. Record a new score of x.
 *
 * - '+'. Record a new score that is the sum of the previous two scores.
 *
 * - 'D'. Record a new score that is the double of the previous score.
 *
 * - 'C'. Invalidate the previous score, removing it from the record.
 *
 * Return the sum of all the scores on the record after applying all the operations.
 *
 * The test cases are generated such that the answer and all intermediate calculations fit in a
 * 32-bit integer and that all operations are valid.
 *
 * ! operations[i] is "C", "D", "+", or a string representing an integer in range [-3*104, 3*104].
 *
 * ! For operation "+", there will always be at least two previous scores on the record.
 *
 * ! For operations "C" and "D", there will always be at least one previous score on the record.
 */

class Solution {
public:
    int calPoints(const std::vector<std::string>& operations)
    {
        if (operations.empty())
            return 0;

        std::stack<int> stack;
        for (const auto& op : operations) {
            if (op == "+" && stack.size() >= 2) {
                const auto v1 = stack.top();
                stack.pop();
                const auto v2 = stack.top();
                stack.push(v1);
                stack.push(v1 + v2);
            } else if (op == "D" && !stack.empty()) {
                const auto v1 = stack.top();
                stack.push(2 * v1);
            } else if (op == "C" && !stack.empty()) {
                stack.pop();
            } else {
                stack.push(std::stoi(op));
            }
        }
        int result = 0;
        while (!stack.empty()) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }
};
