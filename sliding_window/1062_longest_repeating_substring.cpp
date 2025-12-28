#include <string>
#include <unordered_set>

/**
 * Given a string s, return the length of the longest repeating substrings. If no repeating
 * substring exists, return 0.
 *
 * ! 1 <= s.length <= 2000
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int longestRepeatingSubstring(std::string s)
    {
        // binary search + rolling hash
        int lo = 0;
        int hi = s.size();
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(kBase, kMod, mid, s)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    static constexpr long long kBase = 26;
    static constexpr long long kMod = 1e9 + 7;

    // check if there exists a repeated substing of the given length
    bool isValid(long long base, long long mod, long long L, const std::string& s)
    {
        const long long n = s.size();
        long long powMod = 1; // base^(L-1) % mod
        for (long long i = 1; i <= L - 1; ++i) {
            powMod = powMod * base % mod;
        }
        long long hash = 0;
        std::unordered_set<long long> set;
        for (long long i = n - 1; i >= 0; --i) {
            if (i < n - L) {
                hash = (hash - (valueOf(s[i + L]) % mod * powMod) % mod + mod) % mod;
            }
            hash = (hash * (base % mod)) % mod;
            hash = (hash + valueOf(s[i]) % mod) % mod;
            if (set.count(hash))
                return true;

            set.insert(hash);
        }
        return false;
    }

    long long valueOf(char c)
    {
        return c - 'a' + 1;
    }
};
