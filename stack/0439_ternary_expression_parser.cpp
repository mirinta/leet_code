#include <stack>
#include <string>

/**
 * Given a string expression representing arbitrarily nested ternary expressions, evaluate the
 * expression, and return the result of it.
 *
 * You can always assume that the given expression is valid and only contains digits, '?', ':', 'T',
 * and 'F' where 'T' is true and 'F' is false. All the numbers in the expression are one-digit
 * numbers (i.e., in the range [0, 9]).
 *
 * The conditional expressions group right-to-left (as usual in most languages), and the result of
 * the expression will always evaluate to either a digit, 'T' or 'F'.
 *
 * ! 5 <= expression.length <= 10^4
 * ! expression consists of digits, 'T', 'F', '?', and ':'.
 * ! It is guaranteed that expression is a valid ternary expression and that each number is a
 * ! one-digit number.
 */

class Solution {
public:
    std::string parseTernary(std::string expression)
    {
        //       ------|
        // T  ?  2 : 3 |
        //    ^  ------|
        //    i  ^ top of the stack
        std::stack<int> stack;
        int i = expression.size() - 1;
        while (i > 0) {
            if (expression[i] == '?') {
                const auto tVal = stack.top();
                stack.pop();
                stack.pop(); // pop ":"
                const auto fVal = stack.top();
                stack.pop();
                const auto condition = expression[i - 1];
                stack.push(condition == 'T' ? tVal : fVal);
                i -= 2;
            } else {
                stack.push(expression[i--]);
            }
        }
        std::string result;
        if (!stack.empty()) {
            result.push_back(stack.top());
        }
        return result;
    }
};