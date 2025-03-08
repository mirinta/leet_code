#include <array>
#include <string>

/**
 * Given a string s and an integer k, return the number of substrings in s of length k with no
 * repeated characters.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of lowercase English letters.
 * ! 1 <= k <= 10^4
 */

class Solution
{
public:
    int numKLenSubstrNoRepeats(std::string s, int k)
    {
        const int n = s.size();
        std::array<int, 26> count{};
        int result = 0;
        for (int left = 0, right = 0, uniques = 0; right < n; ++right) {
            uniques += ++count[s[right] - 'a'] == 1;
            uniques -= right >= k && --count[s[left++] - 'a'] == 0;
            result += right >= k - 1 && uniques == k;
        }
        return result;
    }
};
