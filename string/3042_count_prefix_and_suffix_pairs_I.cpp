#include <string>
#include <vector>

/**
 * You are given a 0-indexed string array words.
 *
 * Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:
 *
 * - isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and
 * false otherwise.
 *
 * For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and
 * also a suffix, but isPrefixAndSuffix("abc", "abcd") is false.
 *
 * Return an integer denoting the number of index pairs (i, j) such that i < j, and
 * isPrefixAndSuffix(words[i], words[j]) is true.
 *
 * ! 1 <= words.length <= 50
 * ! 1 <= words[i].length <= 10
 * ! words[i] consists only of lowercase English letters.
 */

class Solution {
public:
    int countPrefixSuffixPairs(std::vector<std::string>& words)
    {
        int result = 0;
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i + 1; j < words.size(); ++j) {
                if (isValid(words[i], words[j])) {
                    result++;
                }
            }
        }
        return result;
    }

private:
    bool isValid(const std::string& s1, const std::string& s2)
    {
        if (s1.size() > s2.size())
            return false;

        for (int i = 0; i < s1.size(); ++i) {
            if ((s1[i] != s2[i]) || (s1[i] != s2[s2.size() - s1.size() + i]))
                return false;
        }
        return true;
    }
};