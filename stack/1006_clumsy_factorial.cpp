#include <stack>

/**
 * The factorial of a positive integer n is the product of all positive integers less than or equal
 * to n.
 *
 * - For example, factorial(10) = 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1.
 *
 * We make a clumsy factorial using the integers in decreasing order by swapping out the multiply
 * operations for a fixed rotation of operations with multiply '*', divide '/', add '+', and
 * subtract '-' in this order.
 *
 * - For example, clumsy(10) = 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1.
 *
 * However, these operations are still applied using the usual order of operations of arithmetic. We
 * do all multiplication and division steps before any addition or subtraction steps, and
 * multiplication and division steps are processed left to right.
 *
 * Additionally, the division that we use is floor division such that 10 * 9 / 8 = 90 / 8 = 11.
 *
 * Given an integer n, return the clumsy factorial of n.
 *
 * ! 1 <= n <= 10^4
 */

class Solution {
public:
    int clumsy(int n)
    {
        std::stack<int> stack;
        stack.push(n);
        n--;
        for (int i = 0; n > 0; --n, ++i) {
            if (i % 4 == 0) {
                const int top = stack.top();
                stack.pop();
                stack.push(top * n);
            } else if (i % 4 == 1) {
                const int top = stack.top();
                stack.pop();
                stack.push(top / n);
            } else if (i % 4 == 2) {
                stack.push(n);
            } else {
                stack.push(-n);
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