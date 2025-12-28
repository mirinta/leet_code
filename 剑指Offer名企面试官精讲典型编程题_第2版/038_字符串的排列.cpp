#include <algorithm>
#include <string>
#include <vector>

/**
 * 输入一个字符串，打印出该字符串中字符的所有排列。
 *
 * 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
 *
 * ! 本题与LC 47相同。
 */

class Solution {
public:
    std::vector<std::string> permutation(std::string& s)
    {
        if (s.empty())
            return {};

        // s may contain duplicates
        std::sort(s.begin(), s.end());
        std::vector<bool> visited(s.size(), false);
        std::string permutation;
        backtrack(permutation, visited, s);
        return result;
    }

private:
    std::vector<std::string> result;

    void backtrack(std::string& permutation, std::vector<bool>& visited, const std::string& s)
    {
        if (permutation.size() == s.size()) {
            result.push_back(permutation);
            return;
        }
        for (size_t i = 0; i < s.size(); ++i) {
            if (visited[i])
                continue;

            if (i > 0 && s[i] == s[i - 1] && !visited[i - 1])
                continue;

            visited[i] = true;
            permutation.push_back(s[i]);
            backtrack(permutation, visited, s);
            visited[i] = false;
            permutation.pop_back();
        }
    }
};