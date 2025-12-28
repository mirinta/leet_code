#include <string>

/**
 * A phrase is a palindrome if, after converting all uppercase letters into lowercase and removing
 * all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters
 * include letters and numbers.
 *
 * Given a string "s", return true if it is a palindrome, or false otherwise.
 *
 * ! 1 <= s.length <= 2 * 10^5
 * ! s consists only of printable ASCII characters.
 */

class Solution {
public:
    bool isPalindrome(std::string s)
    {
        const int n = s.size();
        int i = 0;
        int j = n - 1;
        while (true) {
            while (i < n && !std::isalnum(s[i])) {
                i++;
            }
            while (j >= 0 && !std::isalnum(s[j])) {
                j--;
            }
            if (i >= j)
                break;

            if (std::tolower(s[i]) != std::tolower(s[j]))
                return false;

            i++;
            j--;
        }
        return true;
    }
};