#include <array>
#include <string>

/**
 * Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as
 * possible.
 *
 * You can use each character in text at most once. Return the maximum number of instances that can be formed.
 *
 * ! 1 <= text.length <= 10^4
 * ! text consists of lower case English letters only.
 */

class Solution {
public:
    int maxNumberOfBalloons(std::string& text)
    {
        std::array<int, 26> count{};
        for (const auto& c : text) {
            count[c - 'a']++;
        }
        int result = INT_MAX;
        result = std::min(result, count['b' - 'a']);
        result = std::min(result, count['a' - 'a']);
        result = std::min(result, count['l' - 'a'] / 2);
        result = std::min(result, count['o' - 'a'] / 2);
        result = std::min(result, count['n' - 'a']);
        return result;
    }
};