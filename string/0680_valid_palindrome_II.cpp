#include <string>

/**
 * Given a string s, return true if the s can be palindrome after deleting at most one character
 * from it.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    bool validPalindrome(std::string s)
    {
        const int n = s.size();
        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            if (s[i] != s[j])
                return isPalindrome(i + 1, j, s) || isPalindrome(i, j - 1, s);
        }
        return true;
    }

private:
    bool isPalindrome(int start, int end, const std::string& s)
    {
        while (start < end) {
            if (s[start] != s[end])
                return false;

            start++;
            end--;
        }
        return true;
    }
};