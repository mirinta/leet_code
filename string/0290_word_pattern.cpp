#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given a pattern and a string s, find if s follows the same pattern.
 *
 * Here follow means a full match, such that there is a bijection between a letter in pattern and a
 * non-empty word in s.
 *
 * ! 1 <= pattern.length <= 300
 * ! pattern contains only lower-case English letters.
 * ! 1 <= s.length <= 3000
 * ! s contains only lowercase English letters and spaces ' '.
 * ! s does not contain any leading or trailing spaces.
 * ! All the words in s are separated by a single space.
 */

class Solution {
public:
    bool wordPattern(std::string pattern, std::string s)
    {
        const std::vector<std::string> words = splitWords(s);
        if (pattern.size() != words.size())
            return false;

        const int n = pattern.size();
        std::unordered_map<std::string, char> map;
        std::unordered_set<char> used;
        for (int i = 0; i < n; ++i) {
            if (!map.count(words[i])) {
                if (used.count(pattern[i]))
                    return false;

                map[words[i]] = pattern[i];
                used.insert(pattern[i]);
            } else if (map[words[i]] != pattern[i])
                return false;
        }
        return true;
    }

private:
    std::vector<std::string> splitWords(const std::string& s)
    {
        std::vector<std::string> result;
        const int n = s.size();
        int left = 0;
        int right = 0;
        while (true) {
            while (left < n && s[left] == ' ') {
                left++;
            }
            if (left == n)
                break;

            while (right < n && s[right] != ' ') {
                right++;
            }
            if (right - left > 0) {
                result.push_back(s.substr(left, right - left));
            }
            left = right;
            right++;
        }
        return result;
    }
};