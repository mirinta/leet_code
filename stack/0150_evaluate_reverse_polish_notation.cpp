#include <stack>
#include <string>
#include <vector>

/**
 * You are given an array of strings "tokens" that represents an arithmetic expression in a Reverse
 * Polish Notation.
 *
 * Evaluate the expression. Return an integer that represents the value of the expression.
 *
 * Note that:
 *
 * - The valid operators are '+', '-', '*', and '/'.
 *
 * - Each operand may be an integer or another expression.
 *
 * - The division between two integers always truncates toward zero.
 *
 * - There will not be any division by zero.
 *
 * - The input represents a valid arithmetic expression in a reverse polish notation.
 *
 * - The answer and all the intermediate calculations can be represented in a 32-bit integer.
 *
 * ! 1 <= tokens.length <= 10^4
 * ! tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
 */

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens)
    {
        std::stack<int> stack;
        for (const auto& token : tokens) {
            if (token == "+") {
                const auto [v1, v2] = popTwoNumbers(stack);
                stack.push(v1 + v2);
            } else if (token == "-") {
                const auto [v1, v2] = popTwoNumbers(stack);
                stack.push(v1 - v2);
            } else if (token == "*") {
                const auto [v1, v2] = popTwoNumbers(stack);
                stack.push(v1 * v2);
            } else if (token == "/") {
                const auto [v1, v2] = popTwoNumbers(stack);
                stack.push(v1 / v2);
            } else {
                stack.push(std::stoi(token));
            }
        }
        return stack.top();
    }

private:
    std::pair<int, int> popTwoNumbers(std::stack<int>& stack)
    {
        if (stack.size() < 2)
            return {};

        const int val2 = stack.top();
        stack.pop();
        const int val1 = stack.top();
        stack.pop();
        return {val1, val2};
    }
};
