#include <stack>
#include <string>

/**
 * You are given an encoded string s. To decode the string to a tape, the encoded string is read one
 * character at a time and the following steps are taken:
 *
 * - If the character read is a letter, that letter is written onto the tape.
 *
 * - If the character read is a digit d, the entire current tape is repeatedly written d - 1 more
 * times in total.
 *
 * Given an integer k, return the kth letter (1-indexed) in the decoded string.
 *
 * ! 2 <= s.length <= 100
 * ! s consists of lowercase English letters and digits 2 through 9.
 * ! s starts with a letter.
 * ! 1 <= k <= 10^9
 * ! It is guaranteed that k is less than or equal to the length of the decoded string.
 * ! The decoded string is guaranteed to have less than 2^63 letters.
 */

class Solution {
public:
    std::string decodeAtIndex(std::string s, int k)
    {
        const int n = s.size();
        long long count = 0;
        for (int i = 0; i < n; ++i) {
            if (std::isalpha(s[i])) {
                count++;
                if (count == k)
                    return {s[i]};

            } else {
                const long long repeat = s[i] - '0';
                if (count * repeat < k) {
                    count *= repeat;
                } else if (k % count == 0) {
                    return decodeAtIndex(s.substr(0, i), count);
                } else {
                    return decodeAtIndex(s.substr(0, i), k % count);
                }
            }
        }
        return {};
    }
};