#include <array>
#include <string>

/**
 * Given a string s, return true if a permutation of the string could form a palindrome and false
 * otherwise.
 *
 * ! 1 <= s.length <= 5000
 * ! s consists of only lowercase English letters.
 */

class Solution
{
public:
    bool canPermutePalindrome(std::string s)
    {
        const bool isOdd = s.size() % 2;
        std::array<int, 26> count{};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        int countOdd = 0;
        for (const auto& freq : count) {
            countOdd += freq % 2;
            if (isOdd && countOdd > 1)
                return false;

            if (!isOdd && countOdd > 0)
                return false;    
        }
        return true;
    }
};
