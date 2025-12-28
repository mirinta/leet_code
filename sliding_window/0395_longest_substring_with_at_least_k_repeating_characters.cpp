#include <array>
#include <string>

/**
 * Given a string s and an integer k, return the length of the longest substring of s such that the
 * frequency of each character in this substring is greater than or equal to k.
 *
 * If no such substring exists, return 0.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of only lowercase English letters.
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    int longestSubstring(std::string s, int k)
    {
        // let x = num of distinct letters of a subarray
        // x = 1,2,...,26
        // for each x, find the longest subarray such that
        // it contains exactly x distinct letters
        // and the frequency of each letter >= k
        const int n = s.size();
        std::array<int, 26> count{};
        int result = 0;
        for (int x = 1; x <= 26; ++x) {
            std::fill(count.begin(), count.end(), 0);
            int distinct = 0;
            for (int left = 0, right = 0; right < n; ++right) {
                if (count[s[right] - 'a']++ == 0) {
                    distinct++;
                }
                while (distinct > x) {
                    if (--count[s[left] - 'a'] == 0) {
                        distinct--;
                    }
                    left++;
                }
                if (distinct == x && isValid(count, k)) {
                    result = std::max(result, right - left + 1);
                }
            }
        }
        return result;
    }

private:
    bool isValid(const std::array<int, 26>& count, int k)
    {
        for (const auto& val : count) {
            if (val > 0 && val < k)
                return false;
        }
        return true;
    }
};