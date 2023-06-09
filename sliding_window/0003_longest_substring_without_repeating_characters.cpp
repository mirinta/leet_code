#include <string>
#include <unordered_map>

/**
 * Given a string "s", find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3, the answer if "abc", with the length of 3
 *
 * Example 2:
 * Input: s = "bbbbb"
 * Output: 1, the answer is "b", with the length of 1
 *
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3, the answer is "wke", with the length of 3
 */

class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        int result = 0;
        std::unordered_map<char, int> freq;
        // sliding window, elements in range [left, right)
        int left = 0;
        int right = 0;
        while (right < s.size()) {
            const char letter = s[right++];
            freq[letter]++;
            while (freq[letter] > 1) {
                freq[s[left++]]--;
            }
            result = std::max(result, right - left);
        }
        return result;
    }
};