#include <numeric>
#include <stack>
#include <string>
#include <vector>

/**
 * Implement a basic calculator to evaluate a simple expression string.
 *
 * The expression string contains only non-negative integers, '+', '-', '*', '/' operators, and open
 * '(' and closing parentheses ')'. The integer division should truncate toward zero.
 *
 * You may assume that the given expression is always valid. All intermediate results will be in the
 * range of [-2^31, 2^31 - 1].
 *
 * Note: You are not allowed to use any built-in function which evaluates strings as mathematical
 * expressions, such as eval().
 *
 * ! 1 <= s <= 10^4
 * ! s consists of digits, '+', '-', '*', '/', '(', and ')'.
 * ! s is a valid expression.
 */

class Solution {
public:
    int calculate(std::string s)
    {
        std::stack<std::string> stack;
        std::string expression;
        for (const auto& c : s) {
            if (c == '(') {
                stack.push(expression);
                expression.clear();
            } else if (c == ')') {
                expression = stack.top() + std::to_string(solve(expression));
                stack.pop();
            } else {
                expression.push_back(c);
            }
        }
        return solve(expression);
    }

private:
    bool isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    int solve(std::string& expression)
    {
        if (std::isdigit(expression.front())) {
            expression.insert(expression.begin(), '+');
        }
        const int n = expression.size();
        std::vector<int> values;
        int i = 0;
        while (i < n) {
            if (!isOperator(expression[i]))
                continue;

            // - [- 5]
            // ^ |<->|
            // i substr
            int j = isOperator(expression[i]) ? i + 2 : i + 1;
            while (j < expression.size() && std::isdigit(expression[j])) {
                j++;
            }
            const auto val = std::stoll(expression.substr(i + 1, j - i - 1));
            if (expression[i] == '+') {
                values.push_back(val);
            } else if (expression[i] == '-') {
                values.push_back(-val);
            } else if (expression[i] == '*') {
                values.back() *= val;
            } else {
                values.back() /= val;
            }
            i = j;
        }
        return std::accumulate(values.begin(), values.end(), 0);
    }
};