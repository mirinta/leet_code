#include <algorithm>
#include <array>
#include <string>

/**
 * You are given a string word and an integer k.
 *
 * A substring s of word is complete if:
 *
 * - Each character in s occurs exactly k times.
 *
 * - The difference between two adjacent characters is at most 2. That is, for any two adjacent
 * characters c1 and c2 in s, the absolute difference in their positions in the alphabet is at
 * most 2.
 *
 * Return the number of complete substrings of word.
 *
 * A substring is a non-empty contiguous sequence of characters in a string.
 *
 * ! 1 <= word.length <= 10^5
 * ! word consists only of lowercase English letters.
 * ! 1 <= k <= word.length
 */

class Solution {
public:
    int countCompleteSubstrings(std::string word, int k)
    {
        // if s[i:j) is a valid substring, then length = j - i = xk
        // where x is the number of unique characters in s[i:j)
        // since word[i] is lowercase letters, we know that x = 1,2,...,26
        const int n = word.size();
        std::array<int, 26> freq{0};
        int result = 0;
        for (int x = 1; x <= 26 && x * k <= n; ++x) {
            const int length = x * k;
            freq.fill(0);
            for (int left = 0, right = 0; right < n; ++right) {
                if (right > 0 && std::abs(word[right] - word[right - 1]) > 2) {
                    left = right;
                    freq.fill(0);
                }
                freq[word[right] - 'a']++;
                if (right - left + 1 < length)
                    continue;

                if (right - left + 1 > length) {
                    freq[word[left] - 'a']--;
                    left++;
                }
                const int count = std::count_if(freq.begin(), freq.end(), [k](int val) { return val > 0 && val == k; });
                result += count == x;
            }
        }
        return result;
    }
};