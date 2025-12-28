#include <string>
#include <vector>

/**
 * Given an input string s, reverse the order of the words.
 *
 * A word is defined as a sequence of non-space characters. The words in s will be separated by at
 * least one space.
 *
 * Return a string of the words in reverse order concatenated by a single space.
 *
 * Note that s may contain leading or trailing spaces or multiple spaces between two words. The
 * returned string should only have a single space separating the words. Do not include any extra
 * spaces.
 *
 * ! 1 <= s.length <= 10^4
 * ! s contains English letters (upper-case and lower-case), digits, and spaces ' '.
 * ! There is at least one word in s.
 */

class Solution {
public:
    std::string reverseWords(std::string s)
    {
        const int n = s.size();
        std::vector<std::string> words;
        int i = 0;
        while (i < n) {
            while (i < n && s[i] == ' ') {
                i++;
            }
            int j = i;
            while (j < n && s[j] != ' ') {
                j++;
            }
            if (j - i > 0) {
                words.push_back(s.substr(i, j - i));
            }
            i = j;
        }
        std::reverse(words.begin(), words.end());
        std::string result;
        for (int k = 0; k < words.size(); ++k) {
            result.append(words[k]);
            if (k < words.size() - 1) {
                result.push_back(' ');
            }
        }
        return result;
    }
};