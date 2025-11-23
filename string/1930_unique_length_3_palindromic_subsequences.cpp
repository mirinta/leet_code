#include <array>
#include <string>
#include <vector>

/**
 * Given a string s, return the number of unique palindromes of length three that are a subsequence
 * of s.
 *
 * Note that even if there are multiple ways to obtain the same subsequence, it is still only
 * counted once.
 *
 * A palindrome is a string that reads the same forwards and backwards.
 *
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *
 * - For example, "ace" is a subsequence of "abcde".
 *
 * ! 3 <= s.length <= 10^5
 * ! s consists of only lowercase English letters.
 */

class Solution
{
public:
    int countPalindromicSubsequence(std::string s)
    {
        const int n = s.size();
        std::array<std::pair<int, int>, 26>
            seen{}; // seen[i] = {first index, last index} of character i
        seen.fill({-1, -1});
        std::vector<std::array<int, 26>> count(
            n + 1); // count[i][j] = num of character j in nums[0:i-1]
        for (int i = 0; i < n; ++i) {
            const int index = s[i] - 'a';
            if (seen[index].first == -1) {
                seen[index].first = i;
                seen[index].second = i;
            } else {
                seen[index].second = i;
            }
            count[i + 1] = count[i];
            count[i + 1][index]++;
        }
        int result = 0;
        for (const auto& [first, last] : seen) {
            if (first == -1 || first == last)
                continue;

            int sum = 0;
            for (int i = 0; i < 26; ++i) {
                sum += (count[last][i] - count[first + 1][i]) > 0;
            }
            result += sum;
        }
        return result;
    }
};
