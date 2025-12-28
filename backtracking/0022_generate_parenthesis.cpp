#include <string>
#include <vector>

/**
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed
 * parentheses.
 *
 * ! 1 <= n <= 8
 */

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> result;
        std::string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& current, int left, int right, int n)
    {
        if (left < right || left > n || right > n)
            return;

        if (left == right && left == n) {
            result.push_back(current);
            return;
        }
        current.push_back('(');
        backtrack(result, current, left + 1, right, n);
        current.pop_back();
        current.push_back(')');
        backtrack(result, current, left, right + 1, n);
        current.pop_back();
    }
};
