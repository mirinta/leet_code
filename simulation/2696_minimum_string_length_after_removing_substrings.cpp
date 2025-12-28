#include <string>

/**
 * You are given a string s consisting only of uppercase English letters.
 *
 * You can apply some operations to this string where, in one operation, you can remove any
 * occurrence of one of the substrings "AB" or "CD" from s.
 *
 * Return the minimum possible length of the resulting string that you can obtain.
 *
 * Note that the string concatenates after removing the substring and could produce new "AB" or "CD"
 * substrings.
 *
 * ! 1 <= s.length <= 100
 * ! s consists only of uppercase English letters.
 */

class Solution {
public:
    int minLength(std::string s)
    {
        std::string word;
        for (const auto& c : s) {
            word.push_back(c);
            process(word);
        }
        return word.size();
    }

private:
    void process(std::string& word)
    {
        while (word.size() >= 2) {
            const auto tail = word.substr(word.size() - 2, 2);
            if (tail != "AB" && tail != "CD")
                break;

            word.pop_back();
            word.pop_back();
        }
    }
};