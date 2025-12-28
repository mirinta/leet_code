#include <string>
#include <unordered_map>

/**
 * You are given two strings s and t such that every character occurs at most once in s and t is a
 * permutation of s.
 *
 * The permutation difference between s and t is defined as the sum of the absolute difference
 * between the index of the occurrence of each character in s and the index of the occurrence of the
 * same character in t.
 *
 * Return the permutation difference between s and t.
 *
 * ! 1 <= s.length <= 26
 * ! Each character occurs at most once in s.
 * ! t is a permutation of s.
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int findPermutationDifference(std::string s, std::string t)
    {
        const int n = s.size();
        std::unordered_map<char, int> map;
        for (int i = 0; i < n; ++i) {
            map[t[i]] = i;
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::abs(i - map[s[i]]);
        }
        return result;
    }
};