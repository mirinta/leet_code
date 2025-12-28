#include <algorithm>
#include <stack>
#include <string>
#include <vector>

/**
 * A boolean expression is an expression that evaluates to either true or false. It can be in one of
 * the following shapes:
 *
 * - 't' that evaluates to true.
 *
 * - 'f' that evaluates to false.
 *
 * - '!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
 *
 * - '&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner
 * expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
 *
 * - '|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner
 * expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
 *
 * Given a string expression that represents a boolean expression, return the evaluation of that
 * expression.
 *
 * It is guaranteed that the given expression is valid and follows the given rules.
 *
 * ! 1 <= expression.length <= 2 * 10^4
 * !expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
 */

class Solution {
public:
    bool parseBoolExpr(std::string expression)
    {
        std::stack<char> stack;
        for (const auto& c : expression) {
            if (c == ')') {
                std::vector<char> values;
                while (stack.top() != '(') {
                    values.push_back(stack.top());
                    stack.pop();
                }
                stack.pop(); // pop (
                const auto operation = stack.top();
                stack.pop();
                stack.push(helper(operation, values) ? 't' : 'f');
            } else if (c != ',') {
                stack.push(c);
            }
        }
        return stack.top() == 't';
    }

private:
    bool helper(char operation, const std::vector<char>& values)
    {
        if (operation == '!')
            return values.front() != 't';

        if (operation == '&')
            return std::all_of(values.begin(), values.end(), [](const auto& c) { return c == 't'; });

        if (operation == '|')
            return std::any_of(values.begin(), values.end(), [](const auto& c) { return c == 't'; });

        return false;
    }
};