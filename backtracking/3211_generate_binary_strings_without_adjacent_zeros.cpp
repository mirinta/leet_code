#include <string>
#include <vector>

/**
 * You are given a positive integer n.
 *
 * A binary string x is valid if all substrings of x of length 2 contain at least one "1".
 *
 * Return all valid strings with length n, in any order.
 *
 * ! 1 <= n <= 18
 */

class Solution {
public:
    std::vector<std::string> validStrings(int n)
    {
        std::vector<std::string> result;
        std::string sub;
        backtrack(result, sub, 0, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& sub, int i, int n)
    {
        if (i == n) {
            result.push_back(sub);
            return;
        }
        if (sub.empty() || sub.back() == '1') {
            sub.push_back('0');
            backtrack(result, sub, i + 1, n);
            sub.pop_back();
        }
        sub.push_back('1');
        backtrack(result, sub, i + 1, n);
        sub.pop_back();
    }
};
