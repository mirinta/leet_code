#include <utility>

/**
 * Given three integers a, b, and n, return the maximum value of (a XOR x) * (b XOR x) where 0 <= x
 * < 2n.
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * Note that XOR is the bitwise XOR operation.
 *
 * ! 0 <= a, b < 250
 * ! 0 <= n <= 50
 */

class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n)
    {
        constexpr int kMod = 1e9 + 7;
        // a = 1 = 0 0 0 1
        // b = 6 = 0 1 1 0
        // at each bit i
        // - if a[i] = b[i] = 0, then x[i] = 1
        // - if a[i] = b[i] = 1, then x[i] = 0
        // - a[i] != b[i], we always want to increase the smaller number
        //   let a < b, then x[i] = a[i] == 1 ? 0 : 1
        //   then a ^= x and b ^= x
        if (n == 0)
            return a % kMod * (b % kMod) % kMod;

        for (long long bit = 1LL << (n - 1); bit > 0; bit >>= 1) {
            if ((std::min(a, b) & bit) == 0) {
                a ^= bit;
                b ^= bit;
            }
        }
        return a % kMod * (b % kMod) % kMod;
    }
};