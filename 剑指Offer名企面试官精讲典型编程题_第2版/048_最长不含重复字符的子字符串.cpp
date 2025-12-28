#include <string>
#include <unordered_map>

/**
 * 请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。
 *
 * ! s.length <= 40000
 *
 * ! 本题与LC 3相同。
 */

class Solution {
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