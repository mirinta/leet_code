#include <utility>

/**
 * You are given three integers x, y, and z.
 *
 * You have x strings equal to "AA", y strings equal to "BB", and z strings equal to "AB". You want
 * to choose some (possibly all or none) of these strings and concatenate them in some order to form
 * a new string. This new string must not contain "AAA" or "BBB" as a substring.
 *
 * Return the maximum possible length of the new string.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 1 <= x, y, z <= 50
 */

class Solution {
public:
    int longestString(int x, int y, int z)
    {
        // if we only have AA and AB, we must put BB next to AA,
        // the pattern is ...[] AA [] AA [] AA []...
        // - if x = y, then max length = 2(x+y)
        // - if x > y, then max length = 2(y+y+1),
        // e.g. x = 3, y = 1, the longest string is "AA BB AA"
        // - if x < y, then max length = 2(x+x+1),
        // e.g. x = 1, y = 3, the longest string is "BB AA BB"
        // - since x >=1 and y>=1, we can always find a substring in the form of "...BB AA..."
        // now, consider AB
        // - it is valid to concatenate all AB's together, i.e., "AB AB..."
        // - we can insert "AB AB..." between BB and AA in "...BB AA..."
        // - the longest string is "...BB [AB AB...] AA..."
        return 2 * z + 2 * std::min({x + y, y + y + 1, x + x + 1});
    }

private:
    // dp[i][j][k][e]
    // - e = 0, length of the longest string that ends with AA made by x AA's, y BB's, and z AB's
    // - e = 1, length of the longest string that ends with BB made by x AA's, y BB's, and z AB's
    // - e = 2, length of the longest string that ends with AB made by x AA's, y BB's, and z AB's
    // case 1: this round ends with AA, last round should end with {BB, AB}
    // case 2: this round ends with BB, last round should end with {AA}
    // case 3: this round ends with AB, last round should end with {BB, AB}
    int approach1(int x, int y, int z)
    {
        int dp[51][51][51][3] = {0};
        for (int i = 0; i <= x; ++i) {
            for (int j = 0; j <= y; ++j) {
                for (int k = 0; k <= z; ++k) {
                    if (i > 0) {
                        dp[i][j][k][0] = std::max(dp[i - 1][j][k][1], dp[i - 1][j][k][2]) + 2;
                    }
                    if (j > 0) {
                        dp[i][j][k][1] = dp[i][j - 1][k][0] + 2;
                    }
                    if (k > 0) {
                        dp[i][j][k][2] = std::max(dp[i][j][k - 1][1], dp[i][j][k - 1][2]) + 2;
                    }
                }
            }
        }
        return std::max({dp[x][y][z][0], dp[x][y][z][1], dp[x][y][z][2]});
    }
};