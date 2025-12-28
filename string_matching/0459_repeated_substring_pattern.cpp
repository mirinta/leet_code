#include <string>

/**
 * Given a string s, check if it can be constructed by taking a substring of it and appending
 * multiple copies of the substring together.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    bool repeatedSubstringPattern(std::string s)
    {
        // s = a b a b
        // s + s = a b a b a b a b
        //           |<-has s->|
        const auto concat = s + s;
        const auto sub = concat.substr(1, concat.size() - 2);
        return sub.find(s) != std::string::npos;
    }
};