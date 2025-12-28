#include <array>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * Let's define a function countUniqueChars(s) that returns the number of unique characters in s.
 *
 * - For example, calling countUniqueChars(s) if s = "LEETCODE" then "L", "T", "C", "O", "D" are the
 * unique characters since they appear only once in s, therefore countUniqueChars(s) = 5.
 *
 * Given a string s, return the sum of countUniqueChars(t) where t is a substring of s. The test
 * cases are generated such that the answer fits in a 32-bit integer.
 *
 * Notice that some substrings can be repeated so in this case you have to count the repeated ones
 * too.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of uppercase English letters only.
 */

class Solution {
public:
    int uniqueLetterString(std::string s)
    {
        return approach2(s);
    }

private:
    // DP with space optimization, TC = O(N), SC = O(N)
    int approach2(const std::string& s)
    {
        const int n = s.size();
        std::array<std::pair<int, int>, 26> seen{}; // <j1, j2>
        std::fill(seen.begin(), seen.end(), std::make_pair(-1, -1));
        seen[s[0] - 'A'] = {-1, 0};
        int dp = 1;
        int result = dp;
        for (int i = 1; i < n; ++i) {
            auto& [j1, j2] = seen[s[i] - 'A'];
            if (j2 == -1) {
                dp += i + 1;
            } else {
                dp += (i - j2) - (j2 - j1);
            }
            std::swap(j1, j2);
            j2 = i;
            result += dp;
        }
        return result;
    }

    // DP, TC = O(N), SC = O(N)
    int approach1(const std::string& s)
    {
        // dp[i] = sum of countUniqueChars(t) where t is a substring of s and t is ending at s[i]
        // case 1:
        // - s[i] is not in s[0:i-1]
        // - s[i-1:i-1] <= s[i], countUniqueChars += 1
        //   s[i-2:i-1] <= s[i], countUniqueChars += 1
        //   ...
        //   s[0:i-1] <= s[i], countUniqueChars += 1
        //   {} <= s[i], single s[i] is a valid substring ending at s[i]
        // - Thus, dp[i] = dp[i-1] + i + 1
        //
        // case 2:
        // - s[i] appears 1 time in s[0:i-1]
        // - Assume the last occurrence of s[i] in s[0:i-1] = j2
        //   0 <= j2 <= i-1
        //
        // 0 X X X j2 j2+1 X X X i-1 i
        //            |<--0 s[i]-->|
        // |<-------1 s[i]-------->|
        //
        // - s[j2+1:i-1] <= s[i], countUniqueChars += 1
        //   s[j2+2:i-1] <= s[i], countUniqueChars += 1
        //   ...
        //   s[i-1:i-1] <= s[i], countUniqueChars += 1
        //   {} <= s[i], single s[i] is a valid substring ending at s[i]
        // - s[j2:i-1] <= s[i], countUniqueChars -= 1
        //   s[j2-1:i-1] <= s[i], countUniqueChars -= 1
        //   ...
        //   s[0:i-1] <= s[i], countUniqueChars -= 1
        // - Thus, dp[i] = dp[i-1] + (i-j2) - (j2+1)
        //
        // case 3:
        // - s[i] appears at least 2 times in s[0:i-1]
        // - Assume the last occurrence of s[i] in s[0:i-1] = j2
        //   Assume the second last occurrence of s[i] in s[0:i-1] = j1
        //   0 <= j1 < j2 <= i-1
        //
        // 0 X X X j1 j1+1 X X X j2 j2+1 X X X i-1 i
        //                          |<--0 s[i]-->|
        //            |<---------1 s[i]--------->|
        // |<----------at least 2 s[i]---------->|
        //
        // - s[j2+1:i-1] <= s[i], countUniqueChars += 1
        //   s[j2+2:i-1] <= s[i], countUniqueChars += 1
        //   ...
        //   s[i-1:i-1] <= s[i], countUniqueChars += 1
        //   {} <= s[i], single s[i] is a valid substring ending at s[i]
        // - s[j1+1:i-1] <= s[i], countUniqueChars -= 1
        //   s[j1+2:i-1] <= s[i], countUniqueChars -=1
        //   ...
        //   s[j2:i-1] <= s[i], countUniqueChars -=1
        // - s[j1:i-1] <= s[i], countUniqueChars remains the same
        //   s[j1-1:i-1] <= s[i], countUniqueChars remains the same
        //   ...
        //   s[0:i-1] <= s[i], countUniqueChars remains the same
        // - Thus, dp[i] = dp[i-1] + (i-j2) - (j2-j1)
        const int n = s.size();
        std::unordered_map<char, std::pair<int, int>> map; // <j1, j2>
        map[s[0]] = {-1, 0};
        std::vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            if (!map.count(s[i])) {
                dp[i] = dp[i - 1] + i + 1;
                map[s[i]] = {-1, i};
                continue;
            }
            auto& [j1, j2] = map[s[i]];
            dp[i] = dp[i - 1] + (i - j2) - (j2 - j1);
            std::swap(j1, j2);
            j2 = i;
        }
        return std::accumulate(dp.begin(), dp.end(), 0);
    }
};