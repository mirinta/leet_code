/**
 * You are given an integer n.
 *
 * A string s is called good if it contains only lowercase English characters and it is possible to
 * rearrange the characters of s such that the new string contains "leet" as a substring.
 *
 * For example:
 *
 * - The string "lteer" is good because we can rearrange it to form "leetr" .
 *
 * - "letl" is not good because we cannot rearrange it to contain "leet" as a substring.
 * Return the total number of good strings of length n.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    int stringCount(int n)
    {
        // answer = total - #invalid cases
        // #invalid cases = |A ∪ B ∪ C|
        // |A ∪ B ∪ C| = |A| + |B| + |C| - (|A∩B| + |B∩C| + |A∩C|) + |A∩B∩C|
        // |A| = no l = 25^n
        // |B| = at most one e = no e or exactly one e = 25^n + n*25^(n-1)
        // |C| = no e = 25^n
        // |A∩B| = (no l and no e) or (no l and exactly one e) = 24^n + n*24^(n-1)
        // |A∩C| = no l and no t = 24^n
        // |B∩C| = (no t and no e) or (no t and exactly one e) = 24^n + n*24^(n-1)
        // |A∩B∩C| = (no l and no t and no e) or (no l and no t and exactly one e) = 23^n +
        // n*23^(n-1)
        constexpr long long kMod = 1e9 + 7;
        long long result = powmod(26, n, kMod);
        result -= powmod(25, n - 1, kMod) * (75 + n) % kMod;     // |A| + |B| + |C|
        result += powmod(24, n - 1, kMod) * (72 + 2 * n) % kMod; // |A∩B| + |B∩C| + |A∩C|
        result -= powmod(23, n - 1, kMod) * (23 + n) % kMod;
        result %= kMod;
        result = (result + kMod) % kMod; // prevent negative value
        return result;
    }

private:
    // calculate a^b % mod
    long long powmod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};