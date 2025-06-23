#include <array>
#include <cmath>
#include <numeric>
#include <vector>

/**
 * A k-mirror number is a positive integer without leading zeros that reads the same both forward
 * and backward in base-10 as well as in base-k.
 *
 * - For example, 9 is a 2-mirror number. The representation of 9 in base-10 and base-2 are 9 and
 * 1001 respectively, which read the same both forward and backward.
 *
 * - On the contrary, 4 is not a 2-mirror number. The representation of 4 in base-2 is 100, which
 * does not read the same both forward and backward.
 *
 * Given the base k and the number n, return the sum of the n smallest k-mirror numbers.
 * * !
 * ! 2 <= k <= 9
 * ! 1 <= n <= 30
 */

class Solution
{
public:
    long long kMirror(int k, int n)
    {
        std::vector<long long> nums;
        nums.reserve(n);
        long long halfLength = 1;
        while (nums.size() < n) {
            genMirrorNums(nums, k, n, halfLength, false);
            genMirrorNums(nums, k, n, halfLength, true);
            halfLength++;
        }
        return std::accumulate(nums.begin(), nums.end(), 0LL);
    }

private:
    void genMirrorNums(std::vector<long long>& nums, int k, int n, int halfLength, bool evenLength)
    {
        const long long limit = std::pow(10, halfLength);
        for (long long left = limit / 10; nums.size() < n && left < limit; ++left) {
            const auto p = getPalindrome(left, evenLength);
            if (!isKBasePalindrome(p, k))
                continue;

            nums.push_back(p);
        }
    }

    bool isKBasePalindrome(long long val, long long base)
    {
        static std::array<int, 100> digits{};
        digits.fill(0);
        int size = val == 0;
        for (int i = 0; val > 0; ++i) {
            digits[i] = val % base;
            val /= base;
            size++;
        }
        for (int i = 0, j = size - 1; i < j; ++i, --j) {
            if (digits[i] != digits[j])
                return false;
        }
        return true;
    }

    long long getPalindrome(long long left, bool evenLength)
    {
        // let left = xyz
        // if evenLength, result = xyzzyx
        // otherwise, result = xyzyx
        long long reverse = 0;
        long long copy = left;
        long long pow10 = 1;
        while (copy > 0) {
            reverse = reverse * 10 + copy % 10;
            copy /= 10;
            pow10 *= 10;
        }
        if (!evenLength) {
            left /= 10;
        }
        return left * pow10 + reverse;
    }
};
