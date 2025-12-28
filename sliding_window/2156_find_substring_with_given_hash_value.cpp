#include <string>

/**
 * The hash of a 0-indexed string s of length k, given integers p and m, is computed using the
 * following function:
 *
 * hash(s, p, m) = (val(s[0]) * p0 + val(s[1]) * p1 + ... + val(s[k-1]) * pk-1) mod m.
 *
 * Where val(s[i]) represents the index of s[i] in the alphabet from val('a') = 1 to val('z') = 26.
 *
 * You are given a string s and the integers power, modulo, k, and hashValue. Return sub, the first
 * substring of s of length k such that hash(sub, power, modulo) == hashValue.
 *
 * The test cases will be generated such that an answer always exists.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 1 <= k <= s.length <= 2 * 10^4
 * ! 1 <= power, modulo <= 10^9
 * ! 0 <= hashValue < modulo
 * ! s consists of lowercase English letters only.
 * ! The test cases are generated such that an answer always exists.
 */

class Solution {
public:
    std::string subStrHash(std::string s, int power, int modulo, int k, int hashValue)
    {
        // ... n-k-1 n-k ... n-2 n-1
        //           |<---hash1--->|
        //     |<----hash2---->|
        const int n = s.size();
        long long powMod = 1; // p^(k-1) % modulo
        for (int i = 1; i <= k - 1; ++i) {
            powMod = powMod * power % modulo;
        }
        long long hash = 0;
        int firstIndex = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (i < n - k) {
                // +modulo to prevent negative values
                hash = (hash - (valueOf(s[i + k]) % modulo * powMod) % modulo + modulo) % modulo;
            }
            hash = (hash * (power % modulo)) % modulo;
            hash = (hash + valueOf(s[i]) % modulo) % modulo;
            if (i <= n - k && hash == hashValue) {
                firstIndex = i;
            }
        }
        return firstIndex == -1 ? "" : s.substr(firstIndex, k);
    }

private:
    long long valueOf(char c)
    {
        return (c - 'a') + 1;
    }
};