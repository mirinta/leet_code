#include <array>
#include <string>
#include <vector>

/**
 * Given a string s, return the maximum length of a substring such that it contains at most two
 * occurrences of each character.
 *
 * ! 2 <= s.length <= 100
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int maximumLengthSubstring(std::string& s)
    {
        const int n = s.size();
        std::array<int, 26> count{};
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            const int index = s[right] - 'a';
            count[index]++;
            while (count[index] > 2) {
                count[s[left] - 'a']--;
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};