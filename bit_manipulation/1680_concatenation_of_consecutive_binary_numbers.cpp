/**
 * Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations
 * of 1 to n in order, modulo 10^9 + 7.
 *
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    int concatenatedBinary(int n)
    {
        return approach2(n);
    }

private:
    static constexpr long long kMod = 1e9 + 7;

    int approach2(int n)
    {
        long long result = 0;
        for (long long i = 1, length = 0; i <= n; ++i) {
            length += (i & (i - 1)) == 0;
            result = ((result << length) | i) % kMod;
        }
        return result;
    }

    int approach1(int n)
    {
        auto length = [](int n) {
            if (n == 0)
                return 1;

            int result = 0;
            while (n) {
                result++;
                n >>= 1;
            }
            return result;
        };
        long long result = 0;
        for (long long i = 1; i <= n; ++i) {
            result = ((result << length(i)) | i) % kMod;
        }
        return result;
    }
};