#include <array>
#include <vector>

/**
 * You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some
 * coordinate.
 *
 * - For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the
 * letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
 *
 * Given the string word, return the minimum total distance to type such string using only two fingers.
 *
 * The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.
 *
 * Note that the initial positions of your two fingers are considered free so do not count towards your total distance,
 * also your two fingers do not have to start at the first letter or the first two letters.
 *
 * ! 2 <= word.length <= 300
 * ! word consists of uppercase English letters.
 */

class Solution {
public:
    int minimumDistance(std::string& word)
    {
        const int n = word.size();
        Memo memo(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 26; ++j) {
                memo[i][j].fill(-1);
            }
        }
        int result = INT_MAX;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                result = std::min(result, dfs(memo, 0, i, j, word));
            }
        }
        return result;
    }

private:
    using Memo = std::vector<std::array<std::array<int, 26>, 26>>;

    int dfs(Memo& memo, int i, int left, int right, const std::string& s)
    {
        if (i >= s.size())
            return 0;

        if (memo[i][left][right] != -1)
            return memo[i][left][right];

        const int case1 = distance(left, s[i] - 'A') + dfs(memo, i + 1, s[i] - 'A', right, s);
        const int case2 = distance(right, s[i] - 'A') + dfs(memo, i + 1, left, s[i] - 'A', s);
        return memo[i][left][right] = std::min(case1, case2);
    }

    int distance(int id1, int id2)
    {
        const int x1 = id1 / 6;
        const int y1 = id1 % 6;
        const int x2 = id2 / 6;
        const int y2 = id2 % 6;
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
};