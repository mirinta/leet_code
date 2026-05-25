#include <string>
#include <vector>

/**
 * You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning,
 * you are standing at index 0, which is equal to '0'. You can move from index i to index j if the
 * following conditions are fulfilled:
 *
 * - i + minJump <= j <= min(i + maxJump, s.length - 1), and
 *
 * - s[j] == '0'.
 *
 * Return true if you can reach index s.length - 1 in s, or false otherwise.
 *
 * ! 2 <= s.length <= 10^5
 * ! s[i] is either '0' or '1'.
 * ! s[0] == '0'
 * ! 1 <= minJump <= maxJump < s.length
 */

class Solution {
public:
    bool canReach(std::string& s, int minJump, int maxJump)
    {
        // dp[i] = whether we can reach index i
        // if we can move from j to i,
        // then j is in the range of [i-max, i-min]
        // thus, dp[i] = true if there exists a true value in dp[i-max:i-min]
        const int n = s.size();
        std::vector<bool> dp(n, false);
        dp[0] = true;
        for (int i = 1, count = 0; i < n; ++i) {
            if (i - maxJump - 1 >= 0 && dp[i - maxJump - 1]) {
                count--;
            }
            if (i - minJump >= 0 && dp[i - minJump]) {
                count++;
            }
            dp[i] = s[i] == '0' && count > 0;
        }
        return dp[n - 1];
    }
};
