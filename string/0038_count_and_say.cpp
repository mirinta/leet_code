#include <string>

/**
 * The count-and-say sequence is a sequence of digit strings defined by the recursive formula:
 *
 * - countAndSay(1) = "1"
 *
 * - countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then
 * converted into a different digit string.
 *
 * To determine how you "say" a digit string, split it into the minimal number of substrings such
 * that each substring contains exactly one unique digit. Then for each substring, say the number of
 * digits, then say the digit. Finally, concatenate every said digit.
 *
 * Given a positive integer n, return the nth term of the count-and-say sequence.
 *
 * ! 1 <= n <= 30
 */

class Solution {
public:
    std::string countAndSay(int n)
    {
        if (n == 1)
            return "1";

        const auto s = countAndSay(n - 1);
        int i = 0;
        std::string concatenated;
        while (i < s.size()) {
            int j = i + 1;
            while (j < s.size() && s[j] == s[j - 1]) {
                j++;
            }
            concatenated.append(std::to_string(j - i));
            concatenated.push_back(s[i]);
            i = j;
        }
        return concatenated;
    }
};