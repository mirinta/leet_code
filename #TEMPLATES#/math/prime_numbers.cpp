#include <vector>

/**
 * @brief Check whether n is a prime number.
 *
 * @note Time Complexity = O(sqrt(n))
 */
bool isPrimeNumber(int n)
{
    if (n < 2)
        return false;

    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return false;
}

/**
 * @brief Sieve of Eratosthenes.
 *
 * Return all prime numbers within the range [1, n] in ascending order.
 *
 * @note Time Complexity = O(nloglogn)
 */
std::vector<int> getPrimeNumbers(int n)
{
    if (n < 2)
        return {};

    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (long long i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    std::vector<int> result;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            result.push_back(i);
        }
    }
    return result;
}

/**
 * @brief Return the prime factor decomposition of n.
 *
 * @note No duplicates.
 *
 * @note Time Complexity = O(sqrt(n))
 */
std::vector<int> getPrimeFactors(int n)
{
    std::vector<int> result;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            result.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n != 1) {
        result.push_back(n);
    }
    return result;
}

/**
 * @brief Return the prime factor decomposition of n using a preprocessed table of prime numbers,
 * which contains all prime numbers within the range [1, n] in ascending order.
 *
 * @note Time Complexity = O(sqrt(n/logn))
 */
std::vector<int> getPrimeFactors(int n, const std::vector<int>& primesTable)
{
    std::vector<int> result;
    for (const auto& p : primesTable) {
        if (p > n)
            break;

        if (p * p > n) {
            result.push_back(n);
            break;
        }
        if (n % p == 0) {
            result.push_back(p);
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    return result;
}
