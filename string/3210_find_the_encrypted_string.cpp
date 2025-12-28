#include <string>

/**
 * You are given a string s and an integer k. Encrypt the string using the following algorithm:
 *
 * - For each character c in s, replace c with the kth character after c in the string (in a cyclic
 * manner).
 *
 * Return the encrypted string.
 *
 * ! 1 <= s.length <= 100
 * ! 1 <= k <= 10^4
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    std::string getEncryptedString(std::string s, int k)
    {
        const int n = s.size();
        std::string result(n, ' ');
        for (int i = 0; i < n; ++i) {
            result[i] = s[(i + k) % n];
        }
        return result;
    }
};
