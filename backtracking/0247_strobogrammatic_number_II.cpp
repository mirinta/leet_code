#include <string>
#include <unordered_map>
#include <vector>

/**
 * Given an integer n, return all the strobogrammatic numbers that are of length n. You may return
 * the answer in any order.
 *
 * A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at
 * upside down).
 *
 * ! 1 <= n <= 14
 */

class Solution {
public:
    std::vector<std::string> findStrobogrammatic(int n)
    {
        return dfs(n, n);
    }

private:
    const std::unordered_map<char, char> map{{'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'}};

    std::vector<std::string> dfs(int n, int finalLength)
    {
        if (n == 0)
            return {{}};

        if (n == 1)
            return {"0", "1", "8"};

        std::vector<std::string> result;
        for (const auto& s : dfs(n - 2, finalLength)) {
            for (const auto& [head, tail] : map) {
                if (head == '0' && n == finalLength)
                    continue;

                result.push_back(head + s + tail);
            }
        }
        return result;
    }
};