#include <string>
#include <unordered_map>

/**
 * A string s is nice if, for every letter of the alphabet that s contains, it appears both in
 * uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b'
 * appear. However, "abA" is not because 'b' appears, but 'B' does not.
 *
 * Given a string s, return the longest substring of s that is nice. If there are multiple, return
 * the substring of the earliest occurrence. If there are none, return an empty string.
 *
 * ! 1 <= s.length <= 100
 * ! s consists of uppercase and lowercase English letters.
 */

class Solution {
public:
    std::string longestNiceSubstring(std::string s)
    {
        const int n = s.size();
        int startIndex = -1;
        int maxLength = 0;
        for (int x = 2; x <= 52; x += 2) {
            std::unordered_map<char, int> map;
            for (int left = 0, right = 0; right < n; ++right) {
                map[s[right]]++;
                while (map.size() > x) {
                    if (--map[s[left]] == 0) {
                        map.erase(s[left]);
                    }
                    left++;
                }
                const int L = right - left + 1;
                if (!isValid(map) || L < maxLength)
                    continue;

                if (L > maxLength) {
                    maxLength = L;
                    startIndex = left;
                } else {
                    startIndex = std::min(left, startIndex);
                }
            }
        }
        return startIndex == -1 ? "" : s.substr(startIndex, maxLength);
    }

private:
    bool isValid(const std::unordered_map<char, int>& map)
    {
        for (const auto& [c, count] : map) {
            if (std::islower(c) && !map.count(std::toupper(c)))
                return false;

            if (std::isupper(c) && !map.count(std::tolower(c)))
                return false;
        }
        return true;
    }
};