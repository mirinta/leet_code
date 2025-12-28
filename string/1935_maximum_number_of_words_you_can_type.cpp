#include <array>
#include <string>

/**
 * There is a malfunctioning keyboard where some letter keys do not work. All other keys on the
 * keyboard work properly.
 *
 * Given a string text of words separately by a single space (no leading or trailing spaces) and a
 * string brokenLetters of all distinct letter kys that are broken, return the number of words in
 * text you can fully type using this keyboard.
 *
 * ! 1 <= text.length <= 10^4
 * ! 0 <= brokenLetters.length <= 26
 * ! text consists of words separated by a single space without any leading or trailing spaces.
 * ! Each word only consists of lowercase English letters.
 * ! brokenLetters consists of distinct lowercase English letters.
 */

class Solution {
public:
    int canBeTypedWords(std::string text, std::string brokenLetters)
    {
        std::array<int, 26> isValid{};
        isValid.fill(true);
        for (const auto& c : brokenLetters) {
            isValid[c - 'a'] = false;
        }
        int count = 0;
        int result = 0;
        for (const auto& c : text) {
            if (c == ' ') {
                result += count == 0;
                count = 0;
            } else {
                count += !isValid[c - 'a'];
            }
        }
        result += count == 0;
        return result;
    }
};