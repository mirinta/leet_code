#include <string>

/**
 * You are given two strings s and t of the same length and an integer maxCost.
 *
 * You want to change s to t. Changing the ith character of s to ith character of t costs |s[i] -
 * t[i]| (i.e., the absolute difference between the ASCII values of the characters).
 *
 * Return the maximum length of a substring of s that can be changed to be the same as the
 * corresponding substring of t with a cost less than or equal to maxCost. If there is no substring
 * from s that can be changed to its corresponding substring from t, return 0.
 *
 * ! 1 <= s.length <= 10^5
 * ! t.length == s.length
 * ! 0 <= maxCost <= 10^6
 * ! s and t consist of only lowercase English letters.
 */

class Solution {
public:
    int equalSubstring(std::string s, std::string t, int maxCost)
    {
        const int n = s.size();
        int result = 0;
        for (int left = 0, right = 0, cost = 0; right < n; ++right) {
            cost += std::abs(s[right] - t[right]);
            while (cost > maxCost) {
                cost -= std::abs(s[left] - t[left]);
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};