#include <numeric>
#include <string>

/**
 * For two strings s and t, we say "t divides s" if and only if s = t + ... + t (i.e., t is
 * concatenated with itself one or more times).
 *
 * Given two strings str1 and str2, return the largest string x such that x divides both str1 and
 * str2.
 *
 * ! 1 <= str1.length, str2.length <= 1000
 * ! str1 and str2 consist of English uppercase letters.
 */

class Solution {
public:
    std::string gcdOfStrings(std::string str1, std::string str2)
    {
        if (str1 + str2 != str2 + str1)
            return {};

        return str1.substr(0, std::gcd(str1.size(), str2.size()));
    }
};