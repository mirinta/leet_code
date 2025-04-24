#include <unordered_map>
#include <vector>

/**
 * You are given two integers n and maxValue, which are used to describe an ideal array.
 *
 * A 0-indexed integer array arr of length n is considered ideal if the following conditions hold:
 *
 * - Every arr[i] is a value from 1 to maxValue, for 0 <= i < n.
 *
 * - Every arr[i] is divisible by arr[i - 1], for 0 < i < n.
 *
 * Return the number of distinct ideal arrays of length n. Since the answer may be very large,
 * return it modulo 10^9 + 7.
 *
 * ! 2 <= n <= 10^4
 * ! 1 <= maxValue <= 10^4
 */

class Solution
{
public:
    int idealArrays(int n, int maxValue)
    {
        static constexpr long long kMod = 1e9 + 7;
        static const auto primes = [](long long max) {
            std::vector<bool> isPrime(1 + max, true);
            isPrime[0] = false;
            isPrime[1] = false;
            for (long long i = 2; i * i <= max; ++i) {
                if (!isPrime[i])
                    continue;

                for (long long j = i * i; j <= max; j += i) {
                    isPrime[j] = false;
                }
            }
            std::vector<long long> primes;
            for (long long i = 2; i <= max; ++i) {
                if (isPrime[i]) {
                    primes.push_back(i);
                }
            }
            return primes;
        }(1e4);
        static const auto combo = [](int m, int n) {
            std::vector<std::vector<long long>> combo(m, std::vector<long long>(n));
            for (int i = 0; i < m; ++i) {
                combo[i][0] = 1;
            }
            for (int j = 0; j < std::min(m, n); ++j) {
                combo[j][j] = 1;
            }
            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n; ++j) {
                    combo[i][j] = (combo[i - 1][j - 1] + combo[i - 1][j]) % kMod;
                }
            }
            return combo;
        }(1e4 + 14, 14);
        long long result = 0;
        for (long long max = 1; max <= maxValue; ++max) {
            const auto map = primeDecomposition(max, primes);
            long long count = 1;
            for (const auto& [val, freq] : map) {
                count = count * combo[freq + n - 1][freq] % kMod;
            }
            result = (result + count) % kMod;
        }
        return result;
    }

private:
    std::unordered_map<long long, long long> primeDecomposition(
        long long n, const std::vector<long long>& primes)
    {
        std::unordered_map<long long, long long> map;
        for (const auto& p : primes) {
            if (p > n)
                break;

            while (n % p == 0) {
                map[p]++;
                n /= p;
            }
        }
        if (n > 1) {
            map[n]++;
        }
        return map;
    }
};
