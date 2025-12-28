#include <array>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * The appeal of a string is the number of distinct characters found in the string.
 *
 * For example, the appeal of "abbca" is 3 because it has 3 distinct characters: 'a', 'b', and 'c'.
 * Given a string s, return the total appeal of all of its substrings.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    long long appealSum(std::string s)
    {
        return approach2(s);
    }

private:
    // DP with space optimization
    long long approach2(const std::string& s)
    {
        const int n = s.size();
        std::array<int, 26> last{};
        std::fill(last.begin(), last.end(), -1);
        long long dp = 0;
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            const int letter = s[i] - 'a';
            if (last[letter] == -1) {
                dp += i + 1;
            } else {
                dp += i - last[letter];
            }
            last[letter] = i;
            sum += dp;
        }
        return sum;
    }

    // DP
    long long approach1(const std::string& s)
    {
        // dp[i] = total appeal of substrings ending at s[i]
        //
        // substrings ending at s[i] = substrings ending at s[i-1] push_back(s[i])
        // - num of substrings ending at s[i-1] = i
        //
        // case 1: s[i] has never seen before
        // - the appeals of s[i-1:i-1], s[i-2:i-1], ... , s[0:i-1] can increase by 1
        // - single s[i] is also a valid substring
        // - dp[i] = dp[i-1] + (i+1)
        //
        // case 2: assume the last index of s[i] = j
        // - the appeals of s[j+1:i-1], s[j+2:i-1], ..., s[i-1:i-1] can increase by 1
        // - single s[i] is also a valid substring
        // - dp[i] = dp[i-1] + (i-j-1+1)
        const int n = s.size();
        std::vector<long long> dp(n, 0);
        dp[0] = 1;
        std::unordered_map<char, int> map; // last index of char
        map[s[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (!map.count(s[i])) {
                dp[i] = dp[i - 1] + i + 1;
            } else {
                dp[i] = dp[i - 1] + i - map[s[i]];
            }
            map[s[i]] = i;
        }
        return std::accumulate(dp.begin(), dp.end(), 0LL);
    }
};