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
    bool canReach(std::string s, int minJump, int maxJump)
    {
        // dp[i] = whether we can reach index i
        // If there exist an index j in the range [i-max,i-min] and dp[j] = true,
        // then we can reach index i.
        // For each index i, it is not efficient to loop through [i-max,i-min].
        // In fact, we don't need to know the exact value of j.
        // We can count the num of reachable indices in the range [i-max, i-min].
        // - if the count is > 0, then index i is reachable.
        // - for index i, count(i-max,i-max+1,...,i-min)
        // - for index i+1, count(i-max+1,...,i-min,i-min+1)
        // - it is similar to counting using a sliding window
        const int n = s.size();
        std::vector<int> dp(n, false);
        dp[0] = true;
        int count = 0;
        for (int i = 1; i < n; ++i) {
            if (i > maxJump && dp[i - maxJump - 1]) {
                count--;
            }
            if (i >= minJump && dp[i - minJump]) {
                count++;
            }
            dp[i] = s[i] == '0' && count > 0;
        }
        return dp[n - 1];
    }
};