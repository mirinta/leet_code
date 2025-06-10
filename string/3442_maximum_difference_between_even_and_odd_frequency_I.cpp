#include <array>
#include <climits>
#include <string>

/**
 * You are given a string s consisting of lowercase English letters.
 *
 * Your task is to find the maximum difference diff = a1 - a2 between the frequency of characters a1
 * and a2 in the string such that:
 *
 * - a1 has an odd frequency in the string.
 *
 * - a2 has an even frequency in the string.
 *
 * Return this maximum difference.
 *
 * ! 3 <= s.length <= 100
 * ! s consists only of lowercase English letters.
 * ! s contains at least one character with an odd frequency and one with an even frequency.
 */

class Solution
{
public:
    int maxDifference(std::string s)
    {
        std::array<int, 26> count{};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        int maxOdd = INT_MIN;
        int minEven = INT_MAX;
        for (const auto& val : count) {
            if (val == 0)
                continue;

            if (val % 2) {
                maxOdd = std::max(maxOdd, val);
            } else {
                minEven = std::min(minEven, val);
            }
        }
        return maxOdd - minEven;
    }
};
