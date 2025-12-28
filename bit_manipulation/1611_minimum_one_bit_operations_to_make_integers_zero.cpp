#include <unordered_map>

/**
 * Given an integer n, you must transform it into 0 using the following operations any number of
 * times:
 *
 * - Change the rightmost (0th) bit in the binary representation of n.
 *
 * - Change the ith bit in the binary representation of n if the (i-1)th bit is set to 1 and the
 * (i-2)th through 0th bits are set to 0.
 *
 * Return the minimum number of operations to transform n into 0.
 *
 * ! 0 <= n <= 10^9
 */

class Solution {
public:
    int minimumOneBitOperations(int n)
    {
        // if n = 2^k, then #operations = 2^(1+k)-1
        // examples:
        // - n = 1 = 2^0, #operations = 2-1 = 1
        // - n = 2 = 2^1, #operations = 4-1 = 3
        // - n = 4 = 2^2, #operations = 8-1 = 7
        // - n = 16 = 2^4, #operations = 32-1 = 31

        // the binary representation of a five bits number can be written as 1abcd
        // the process of transforming 1abcd to 00000:
        // 1[abcd] -> 1[1000] -> 0[1000] -> transform 1000 to 0000
        // #operations = transform abcd to 1000 + 1 + transform 1000 to 0000

        // how to transform abcd to 1000?
        // case 1, a = 1
        // - 1bcd -> 1(000)
        // - #operations = transform bcd to 000
        // case 2, a = 0
        // - 0bcd -> 0(100) -> 1(100) -> 1(000)
        // - #operations = transform bcd to 100 + 1 + transform 100 to 000
        return transNto0(n);
    }

private:
    struct pair_hash {
        template<typename T1, typename T2>
        size_t operator()(const std::pair<T1, T2>& p) const
        {
            const auto hash1 = std::hash<T1>()(p.first);
            const auto hash2 = std::hash<T2>()(p.second);
            if (hash1 == hash2)
                return hash1;

            return hash2;
        }
    };

    std::unordered_map<int, int> memo1;
    std::unordered_map<std::pair<int, int>, int, pair_hash> memo2;

    int transNto0(int n)
    {
        if (n == 0)
            return 0;

        if (n == 1)
            return 1;

        if (memo1.count(n))
            return memo1[n];

        const int bits = countBits(n);
        const int mask = (1 << (bits - 1)) - 1;
        return memo1[n] = transNtoPowOf2(mask & n, bits - 1) + 1 + transPowOf2To0(bits - 1);
    }

    int transNtoPowOf2(int n, int bits)
    {
        if (n == 0 && bits == 1)
            return 1;

        const auto args = std::make_pair(n, bits);
        if (memo2.count(args))
            return memo2[args];

        const int mask = 1 << (bits - 1);
        if (n & mask)
            return memo2[args] = transNto0((mask - 1) & n);

        return memo2[args] = transNtoPowOf2((mask - 1) & n, bits - 1) + 1 + transPowOf2To0(bits - 1);
    }

    int transPowOf2To0(int bits)
    {
        return (1 << bits) - 1;
    }

    int countBits(int n)
    {
        int bits = 0;
        while (n) {
            bits++;
            n >>= 1;
        }
        return bits;
    }
};