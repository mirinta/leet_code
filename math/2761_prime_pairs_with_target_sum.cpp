#include <vector>

/**
 * You are given an integer n. We say that two integers x and y form a prime number pair if:
 *
 * - 1 <= x <= y <= n
 *
 * - x + y == n
 *
 * - x and y are prime numbers
 *
 * Return the 2D sorted list of prime number pairs [xi, yi]. The list should be sorted in increasing
 * order of xi. If there are no prime number pairs at all, return an empty array.
 *
 * Note: A prime number is a natural number greater than 1 with only two factors, itself and 1.
 *
 * ! 1 <= n <= 10^6
 */

class Solution {
public:
    std::vector<std::vector<int>> findPrimePairs(int n)
    {
        if (n < 4)
            return {};

        std::vector<bool> isPrime(n + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (int i = 2; i * i <= n; ++i) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        std::vector<std::vector<int>> result;
        for (int i = 2; i <= n; ++i) {
            if (!isPrime[i] || !isPrime[n - i])
                continue;

            result.push_back({i, n - i});
            isPrime[i] = false;     // prevent duplicates
            isPrime[n - i] = false; // prevent duplicates
        }
        return result;
    }
};