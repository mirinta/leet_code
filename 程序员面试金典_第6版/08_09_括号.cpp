#include <string>
#include <vector>

/**
 * 括号。设计一种算法，打印n对括号的所有合法的（例如，开闭一一对应）组合。
 *
 * 说明：解集不能包含重复的子集。
 */

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n)
    {
        std::vector<std::string> result;
        std::string path;
        backtrack(result, path, n, n);
        return result;
    }

private:
    void backtrack(std::vector<std::string>& result, std::string& path, int left, int right)
    {
        if (left > right || left < 0 || right < 0)
            return;

        if (left == 0 && right == 0) {
            result.push_back(path);
            return;
        }
        path.push_back('(');
        backtrack(result, path, left - 1, right);
        path.pop_back();
        path.push_back(')');
        backtrack(result, path, left, right - 1);
        path.pop_back();
    }
};