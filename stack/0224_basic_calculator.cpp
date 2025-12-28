#include <stack>
#include <string>

/**
 * Given a string s representing a valid expression, implement a basic calculator to evaluate it,
 * and return the result of the evaluation.
 *
 * Note: You are not allowed to use any built-in function which evaluates strings as mathematical
 * expressions, such as eval().
 *
 * ! 1 <= s.length <= 3 * 10^5
 * ! s consists of digits, '+', '-', '(', ')', and ' '.
 * ! s represents a valid expression.
 * ! '+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
 * ! '-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
 * ! There will be no two consecutive operators in the input.
 * ! Every number and running calculation will fit in a signed 32-bit integer.
 */

class Solution {
public:
    int calculate(std::string s)
    {
        std::string expression;
        std::stack<std::string> stack;
        for (const auto& c : s) {
            if (c == '+' || c == '-' || std::isdigit(c)) {
                expression.push_back(c);
            } else if (c == '(') {
                stack.push(expression);
                expression.clear();
            } else if (c == ')') {
                expression = stack.top() + std::to_string(solve(expression));
                stack.pop();
            }
        }
        return solve(expression);
    }

private:
    int solve(std::string& expression)
    {
        // --5 should be treated as 5
        // +-2 should be treated as -2
        if (std::isdigit(expression.front())) {
            expression.insert(expression.begin(), '+');
        }
        const int n = expression.size();
        int result = 0;
        int i = 0;
        while (i < n) {
            // - [- 5]
            // ^ |<->|
            // i  val
            const int sign = expression[i] == '+' ? 1 : -1;
            int j = std::isdigit(expression[i + 1]) ? i + 1 : i + 2;
            int val = 0;
            while (j < n && std::isdigit(expression[j])) {
                val = val * 10 + (expression[j] - '0');
                j++;
            }
            if (expression[i + 1] == '-') {
                val *= -1;
            }
            result += sign * val;
            i = j;
        }
        return result;
    }
};
