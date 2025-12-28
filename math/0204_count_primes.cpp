#include <vector>

/**
 * Given an integer n, return the number of prime numbers that are strictly less than n.
 *
 * ! 0 <= n <= 5 * 10^6
 */

class Solution {
public:
    int countPrimes(int n)
    {
        if (n < 2)
            return 0;

        std::vector<bool> isPrime(n, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (int i = 2; i * i <= n; ++i) {
            // if i is a prime number,
            // then i*i,i*(i+1),... are not prime numbers
            if (isPrime[i]) {
                for (int j = i * i; j < n; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        int result = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                result++;
            }
        }
        return result;
    }
};