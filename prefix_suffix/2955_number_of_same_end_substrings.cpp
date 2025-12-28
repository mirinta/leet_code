#include <array>
#include <string>
#include <vector>

/**
 * You are given a 0-indexed string s, and a 2D array of integers queries, where queries[i] = [li,
 * ri] indicates a substring of s starting from the index li and ending at the index ri (both
 * inclusive), i.e. s[li..ri].
 *
 * Return an array ans where ans[i] is the number of same-end substrings of queries[i].
 *
 * A 0-indexed string t of length n is called same-end if it has the same character at both of its
 * ends, i.e., t[0] == t[n - 1].
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 2 <= s.length <= 3 * 10^4
 * ! s consists only of lowercase English letters.
 * ! 1 <= queries.length <= 3 * 10^4
 * ! queries[i] = [li, ri]
 * ! 0 <= li <= ri < s.length
 */

class Solution {
public:
    std::vector<int> sameEndSubstringCount(std::string s, std::vector<std::vector<int>>& queries)
    {
        const int n = s.size();
        // count[i][j] = num of character j in s[0:i-1]
        std::vector<std::array<int, 26>> count(n + 1);
        for (int i = 1; i <= n; ++i) {
            count[i] = count[i - 1];
            count[i][s[i - 1] - 'a']++;
        }
        const int m = queries.size();
        std::vector<int> result(m);
        for (int i = 0; i < m; ++i) {
            const auto& left = queries[i][0];
            const auto& right = queries[i][1];
            for (int j = 0; j < 26; ++j) {
                const int freq = count[right + 1][j] - count[left][j];
                result[i] += (freq + 1) * freq / 2;
            }
        }
        return result;
    }
};