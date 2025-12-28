#include <string>

/**
 * You are given three strings s1, s2, and s3. You have to perform the following operation on these
 * three strings as many times as you want.
 *
 * In one operation you can choose one of these three strings such that its length is at least 2 and
 * delete the rightmost character of it.
 *
 * Return the minimum number of operations you need to perform to make the three strings equal if
 * there is a way to make them equal, otherwise, return -1.
 *
 * ! 1 <= s1.length, s2.length, s3.length <= 100
 * ! s1, s2 and s3 consist only of lowercase English letters.
 */

class Solution {
public:
    int findMinimumOperations(std::string s1, std::string s2, std::string s3)
    {
        const int n = std::min({s1.size(), s2.size(), s3.size()});
        int i = 0;
        while (i < n && s1[i] == s2[i] && s1[i] == s3[i]) {
            i++;
        }
        return i == 0 ? -1 : s1.size() + s2.size() + s3.size() - 3 * i;
    }
};