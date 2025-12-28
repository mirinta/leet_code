#include <string>
#include <vector>

/**
 * You are given a string s of lowercase English letters and a 2D integer array shifts where
 * shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index
 * starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward
 * if directioni = 0.
 *
 * Shifting a character forward means replacing it with the next letter in the alphabet (wrapping
 * around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with
 * the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').
 *
 * Return the final string after all such shifts to s are applied.
 *
 * ! 1 <= s.length, shifts.length <= 5 * 10^4
 * ! shifts[i].length == 3
 * ! 0 <= starti <= endi < s.length
 * ! 0 <= directioni <= 1
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    std::string shiftingLetters(const std::string& s, const std::vector<std::vector<int>>& shifts)
    {
        const int n = s.size();
        // diff[i] = total shift of s[i:n-1]
        std::vector<int> diff(n, 0);
        for (const auto& shift : shifts) {
            const auto& start = shift[0];
            const auto& end = shift[1];
            const int offset = shift[2] == 0 ? -1 : 1;
            diff[start] = (diff[start] + offset + 26) % 26;
            if (end + 1 < n) {
                diff[end + 1] = (diff[end + 1] - offset + 26) % 26;
            }
        }
        std::string result;
        result.reserve(s.size());
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                diff[i] = (diff[i] + diff[i - 1]) % 26;
            }
            result.push_back((s[i] - 'a' + diff[i]) % 26 + 'a');
        }
        return result;
    }
};
