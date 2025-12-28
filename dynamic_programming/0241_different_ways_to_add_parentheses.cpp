#include <string>
#include <vector>

/**
 * Given a string expression of numbers and operators, return all possible results from computing
 * all the different possible ways to group numbers and operators. You may return the answer in any
 * order.
 *
 * The test cases are generated such that the output values fit in a 32-bit integer and the number
 * of different results does not exceed 10^4.
 *
 * ! 1 <= expression.length <= 20
 * ! expression consists of digits and the operator '+', '-', and '*'.
 * ! All the integer values in the input expression are in the range [0, 99].
 */

class Solution {
public:
    std::vector<int> diffWaysToCompute(std::string expression)
    {
        const int n = expression.size();
        Memo memo(n, std::vector<std::vector<int>>(n));
        return solve(memo, 0, n - 1, expression);
    }

private:
    using Memo = std::vector<std::vector<std::vector<int>>>;

    std::vector<int> solve(Memo& memo, int lo, int hi, const std::string& s)
    {
        if (!memo[lo][hi].empty())
            return memo[lo][hi];

        std::vector<int> result;
        const int length = hi - lo + 1;
        if (length == 0)
            return result;

        if (length == 1) {
            result.push_back(s[lo] - '0');
            return result;
        }
        if (length == 2 && std::isdigit(s[lo])) {
            result.push_back(10 * (s[lo] - '0') + (s[hi] - '0'));
            return result;
        }
        for (int i = lo; i <= hi; ++i) {
            if (std::isdigit(s[i]))
                continue;

            const auto left = solve(memo, lo, i - 1, s);
            const auto right = solve(memo, i + 1, hi, s);
            for (const auto& val1 : left) {
                for (const auto& val2 : right) {
                    if (s[i] == '+') {
                        result.push_back(val1 + val2);
                    } else if (s[i] == '-') {
                        result.push_back(val1 - val2);
                    } else if (s[i] == '*') {
                        result.push_back(val1 * val2);
                    }
                }
            }
        }
        return memo[lo][hi] = result;
    }
};
