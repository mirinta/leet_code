#include <algorithm>
#include <array>
#include <string>

/**
 * You are given a 0-indexed string s consisting of only lowercase English letters, and an integer
 * count. A substring of s is said to be an equal count substring if, for each unique letter in the
 * substring, it appears exactly count times in the substring.
 *
 * Return the number of equal count substrings in s.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 1 <= s.length <= 3 * 10^4
 * ! 1 <= count <= 3 * 10^4
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int equalCountSubstrings(std::string s, int count)
    {
        // if subarray s[j:i] is valid,
        // num of unique letters * count = length = i-j+1
        // since the given string contains only lowercase English letter,
        // then num of unique letters = 1,2,...,26
        const int n = s.size();
        auto predicate = [&count](const auto& val) { return val == 0 || val == count; };
        std::array<int, 26> freq{};
        int result = 0;
        for (int uniques = 1; uniques <= 26; ++uniques) {
            const int L = uniques * count;
            std::fill(freq.begin(), freq.end(), 0);
            for (int left = 0, right = 0; right < n; ++right) {
                freq[s[right] - 'a']++;
                if (right - left + 1 > L) {
                    freq[s[left] - 'a']--;
                    left++;
                }
                if (right - left + 1 == L && std::all_of(freq.begin(), freq.end(), predicate)) {
                    result++;
                }
            }
        }
        return result;
    }
};