#include <string>
#include <unordered_set>
#include <vector>

/**
 * Given a binary string s, partition the string into one or more substrings such that each
 * substring is beautiful.
 *
 * A string is beautiful if:
 *
 * - It doesn't contain leading zeros.
 *
 * - It's the binary representation of a number that is a power of 5.
 *
 * Return the minimum number of substrings in such partition. If it is impossible to partition the
 * string s into beautiful substrings, return -1.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * ! 1 <= s.length <= 15
 * ! s[i] is either '0' or '1'.
 */

class Solution {
public:
    int minimumBeautifulSubstrings(const std::string& s)
    {
        if (s.empty() || s.front() != '1')
            return -1;

        // since s.size() <= 15,
        // we can enumerate all numbers that is a power of 5 within the range [1,1<<15)
        std::unordered_set<int> powOf5;
        int val = 1;
        while (val < (1 << 15)) {
            powOf5.insert(val);
            val *= 5;
        }
        const int n = s.size();
        // dp[i] = min num of beautiful substrings of s[0:i)
        // X X X X X X j X X X X X X X i
        // |<-dp[j]->| |<--pow of 5->|
        // |<---------dp[i]--------->|
        std::vector<int> dp(n + 1, INT_MAX / 2);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (s[j] == '0')
                    continue;

                if (powOf5.count(getValue(j, i - 1, s))) {
                    dp[i] = std::min(dp[i], dp[j] + 1);
                }
            }
        }
        return dp[n] == INT_MAX / 2 ? -1 : dp[n];
    }

private:
    int getValue(int lo, int hi, const std::string& s)
    {
        int val = 0;
        while (lo <= hi) {
            val = val * 2 + (s[lo] - '0');
            lo++;
        }
        return val;
    }
};