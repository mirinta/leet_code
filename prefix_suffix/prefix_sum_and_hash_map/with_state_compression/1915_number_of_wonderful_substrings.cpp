#include <array>
#include <string>
#include <vector>

/**
 * A wonderful string is a string where at most one letter appears an odd number of times.
 *
 * - For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
 *
 * Given a string word that consists of the first ten lowercase English letters ('a' through 'j'),
 * return the number of wonderful non-empty substrings in word. If the same substring appears
 * multiple times in word, then count each occurrence separately.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * ! 1 <= word.length <= 10^5
 * ! word consists of lowercase English letters from 'a' to 'j'.
 */

class Solution {
public:
    long long wonderfulSubstrings(std::string word)
    {
        // prefix[i][c] = frequency of letter c in word[0:i]
        // if word[j+1:i] is a valid subarray
        // - case 1, for each c, prefix[i][c]-prefix[j][c] = even number
        // - case 2, only one c1 that prefix[i][c1]-prefix[j][c1] = odd number
        // and all the other c satisfies prefix[i][c]-prefix[j][c] = even number
        const int n = word.size();
        std::array<int, 1 << 10> count{}; // num of occurrences of state i
        count[0] = 1;
        long long result = 0;
        // state[j] = 0/1 if letter j appears even/odd num of times
        for (int i = 0, state = 0; i < n; ++i) {
            state ^= 1 << (word[i] - 'a');
            result += count[state];
            for (int j = 0; j < 10; ++j) {
                result += count[state ^ (1 << j)];
            }
            count[state]++;
        }
        return result;
    }
};