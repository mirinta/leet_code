#include <string>

/**
 * You are given two 0-indexed strings str1 and str2.
 *
 * In an operation, you select a set of indices in str1, and for each index i in the set, increment
 * str1[i] to the next character cyclically. That is 'a' becomes 'b', 'b' becomes 'c', and so on,
 * and 'z' becomes 'a'.
 *
 * Return true if it is possible to make str2 a subsequence of str1 by performing the operation at
 * most once, and false otherwise.
 *
 * Note: A subsequence of a string is a new string that is formed from the original string by
 * deleting some (possibly none) of the characters without disturbing the relative positions of the
 * remaining characters.
 *
 * ! 1 <= str1.length <= 10^5
 * ! 1 <= str2.length <= 10^5
 * ! str1 and str2 consist of only lowercase English letters.
 */

class Solution {
public:
    bool canMakeSubsequence(std::string str1, std::string str2)
    {
        const int n1 = str1.size();
        const int n2 = str2.size();
        for (int i = 0, j = 0; i < n1; ++i) {
            if (str1[i] == str2[j] || (str1[i] - 'a' + 1) % 26 + 'a' == str2[j]) {
                j++;
            }
            if (j == n2)
                return true;
        }
        return false;
    }
};