#include <array>
#include <string>
#include <vector>

/**
 * You are given a square board of characters. You can move on the board starting at the bottom
 * right square marked with the character 'S'.
 *
 * You need to reach the top left square marked with the character 'E'. The rest of the squares are
 * labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can
 * go up, left or up-left (diagonally) only if there is no obstacle there.
 *
 * Return a list of two integers: the first integer is the maximum sum of numeric characters you can
 * collect, and the second is the number of such paths that you can take to get that maximum sum,
 * taken modulo 10^9 + 7.
 *
 * In case there is no path, return [0, 0].
 *
 * ! 2 <= board.length == board[i].length <= 100
 */

class Solution {
public:
    std::vector<int> pathsWithMaxScore(std::vector<std::string>& board)
    {
        // dp[i][j][0] = max sum of path from (n-1,n-1) to (i,j)
        // dp[i][j][1] = num of paths from (n-1,n-1) to (i,j) such that path sum = dp[i][j][0]
        constexpr int kMod = 1e9 + 7;
        const int n = board.size();
        std::vector<std::vector<std::array<int, 2>>> dp(n, std::vector<std::array<int, 2>>(n, {-1, 0}));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i == n - 1 && j == n - 1) {
                    dp[i][j] = {0, 1};
                    continue;
                }
                if (board[i][j] == 'X')
                    continue;

                const int val = std::isdigit(board[i][j]) ? board[i][j] - '0' : 0;
                int case1 = -1;
                int case2 = -1;
                int case3 = -1;
                if (i + 1 < n && dp[i + 1][j][0] != -1) {
                    case1 = val + dp[i + 1][j][0];
                }
                if (j + 1 < n && dp[i][j + 1][0] != -1) {
                    case2 = val + dp[i][j + 1][0];
                }
                if (i + 1 < n && j + 1 < n && dp[i + 1][j + 1][0] != -1) {
                    case3 = val + dp[i + 1][j + 1][0];
                }
                dp[i][j][0] = std::max({case1, case2, case3});
                if (dp[i][j][0] == -1)
                    continue;

                if (dp[i][j][0] == case1) {
                    dp[i][j][1] = (dp[i][j][1] + dp[i + 1][j][1]) % kMod;
                }
                if (dp[i][j][0] == case2) {
                    dp[i][j][1] = (dp[i][j][1] + dp[i][j + 1][1]) % kMod;
                }
                if (dp[i][j][0] == case3) {
                    dp[i][j][1] = (dp[i][j][1] + dp[i + 1][j + 1][1]) % kMod;
                }
            }
        }
        if (dp[0][0][0] == -1)
            return {0, 0};

        return {dp[0][0][0], dp[0][0][1]};
    }
};