#include <array>
#include <string>
#include <vector>

/**
 * A subsequence of a string is a new string that is formed from the original string by deleting
 * some (can be none) of the characters without disturbing the relative positions of the remaining
 * characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 *
 * Given two strings source and target, return the minimum number of subsequences of source such
 * that their concatenation equals target. If the task is impossible, return -1.
 *
 * ! 1 <= source.length, target.length <= 1000
 * ! source and target consist of lowercase English letters.
 */

class Solution
{
public:
    int shortestWay(std::string source, std::string target)
    {
        // next[i][c] = the smallest index of character c in source[i:n-1]
        const int n = source.size();
        std::vector<std::array<int, 26>> next(n + 1);
        next.back().fill(-1);
        for (int i = n - 1; i >= 0; --i) {
            next[i] = next[i + 1];
            next[i][source[i] - 'a'] = i;
        }
        int i = 0; // scan source
        int j = 0; // scan target
        int result = 1;
        while (j < target.size()) {
            if (next[i][target[j] - 'a'] != -1) {
                i = next[i][target[j] - 'a'] + 1;
                j++;
            } else if (i == 0) {
                // i = 0 && next[i][target[j] - 'a'] == -1
                // it means target[j] can not be found in source[0:n-1]
                return -1;
            } else {
                // i != 0 && next[i][target[j] - 'a'] == -1
                // target[j] can not be found in source[i:n-1]
                // but it may be found in source[0:n-1]
                // so we reset i = 0
                result++;
                i = 0;
            }
        }
        return result;
    }
};
