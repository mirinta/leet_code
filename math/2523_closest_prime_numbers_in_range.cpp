#include <climits>
#include <vector>

/**
 * Given two positive integers left and right, find the two integers num1 and num2 such that:
 *
 * - left <= num1 < num2 <= right .
 *
 * - Both num1 and num2 are prime numbers.
 *
 * - num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
 *
 * Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying
 * these conditions, return the one with the smallest num1 value. If no such numbers exist, return
 * [-1, -1].
 *
 * ! 1 <= left <= right <= 10^6
 */

class Solution {
public:
    std::vector<int> closestPrimes(int left, int right)
    {
        std::vector<bool> isPrime(right + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (long long i = 2; i <= right; ++i) {
            if (!isPrime[i])
                continue;

            for (long long j = i * i; j <= right; j += i) {
                isPrime[j] = false;
            }
        }
        std::vector<int> primes;
        for (int val = left; val <= right; ++val) {
            if (isPrime[val]) {
                primes.push_back(val);
            }
        }
        int minDiff = INT_MAX;
        std::vector<int> result{-1, -1};
        for (int i = 0; i + 1 < primes.size(); ++i) {
            const int diff = primes[i + 1] - primes[i];
            if (diff < minDiff) {
                minDiff = diff;
                result = {primes[i], primes[i + 1]};
            }
        }
        return result;
    }
};
