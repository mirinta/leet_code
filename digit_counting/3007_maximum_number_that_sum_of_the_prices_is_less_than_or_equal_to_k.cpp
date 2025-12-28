#include <limits>
#include <utility>

/**
 * You are given an integer k and an integer x.
 *
 * Consider s is the 1-indexed binary representation of an integer num. The price of a number num is
 * the number of i's such that i % x == 0 and s[i] is a set bit.
 *
 * Return the greatest integer num such that the sum of prices of all numbers from 1 to num is less
 * than or equal to k.
 *
 * Note:
 *
 * - In the binary representation of a number set bit is a bit of value 1.
 *
 * - The binary representation of a number will be indexed from right to left. For example, if s ==
 * 11100, s[4] == 1 and s[2] == 0.
 *
 * ! 1 <= k <= 10^15
 * ! 1 <= x <= 8
 */

class Solution {
public:
    long long findMaximumNumber(long long k, int x)
    {
        long long lo = 1;
        long long hi = LLONG_MAX;
        while (lo < hi) {
            const auto mid = hi - (hi - lo) / 2;
            if (isValid(mid, k, x)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    // check the total prices of all numbers in [1,max] is less than or equal to k
    bool isValid(long long max, long long k, int x)
    {
        // given the ith bit of max = max[i]
        // count the number of v <= max such that v[i] = 1
        // max (binary): |<---LEFT--->| i |<---RIGHT--->|
        //   v (binary): |<--v_left-->| 1 |<--v_right-->|
        //
        // let n = bits of max
        // then bits of RIGHT = i, bits of LEFT = n-i-1
        //
        // if max[i] = 1,
        // - v_left can be [00...0,LEFT-1] and v_right can be any number
        // - v_left can be [LEFT] and v_right can be [000...0,RIGHT]
        // - count = LEFT * 2^(bits of RIGHT) + (RIGHT+1)
        //
        // if max[i] = 0,
        // - v_left can be [00...0,LEFT-1] and v_right can be any number
        // - count = LEFT * 2^(bits of RIGHT)
        const int n = numOfBits(max);
        long long powerOf2 = 1; // 2^i
        long long total = 0;
        for (int i = 0; i < n; ++i, powerOf2 *= 2) {
            if ((i + 1) % x != 0) // turn to 1-indexed
                continue;

            const auto [left, right] = parse(max, i);
            if ((max >> i) & 1) {
                total += left * powerOf2 + right + 1;
            } else {
                total += left * powerOf2;
            }
            if (total > k)
                return false;
        }
        return true;
    }

    int numOfBits(long long val)
    {
        int result = 0;
        while (val) {
            result++;
            val >>= 1;
        }
        return result;
    }

    std::pair<long long, long long> parse(long long val, int i)
    {
        constexpr int kBits = CHAR_BIT * sizeof(long long);
        // L L L L L L i R R R R R R
        // |<--LEFT->|   |<-RIGHT->|
        return {i + 1 == kBits ? 0 : val >> (i + 1), val & ((1LL << i) - 1)};
    }
};