#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums, and you can perform the following operation any number of
 * times on nums:
 *
 * - Swap the positions of two elements nums[i] and nums[j] if gcd(nums[i], nums[j]) > 1 where
 * gcd(nums[i], nums[j]) is the greatest common divisor of nums[i] and nums[j].
 *
 * Return true if it is possible to sort nums in non-decreasing order using the above swap method,
 * or false otherwise.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! 2 <= nums[i] <= 10^5
 */

class UnionFind {
public:
    explicit UnionFind(int n) : root(n), size(n, 1)
    {
        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }
    }

    int find(int x)
    {
        if (x != root[x]) {
            root[x] = find(root[x]);
        }
        return root[x];
    }

    bool isConnected(int p, int q)
    {
        return find(p) == find(q);
    }

    void connect(int p, int q)
    {
        const int rootP = find(p);
        const int rootQ = find(q);
        if (rootP == rootQ)
            return;

        if (size[rootQ] > size[rootP]) {
            root[rootP] = rootQ;
            size[rootQ] += size[rootP];
        } else {
            root[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }
    }

private:
    std::vector<int> root;
    std::vector<int> size;
};

class Solution {
public:
    bool gcdSort(std::vector<int>& nums)
    {
        const int n = nums.size();
        const auto primes = getPrimes(*std::max_element(nums.begin(), nums.end()));
        const int m = primes.size();
        std::unordered_map<int, int> map;
        for (int j = 0; j < m; ++j) {
            map[primes[j]] = j;
        }
        UnionFind uf(n + m);
        for (int i = 0; i < n; ++i) {
            for (const auto& p : getPrimeFactors(nums[i], primes)) {
                uf.connect(i, n + map[p]);
            }
        }
        std::vector<std::pair<int, int>> pairs(n); // val to original index
        for (int i = 0; i < n; ++i) {
            pairs[i].first = nums[i];
            pairs[i].second = i;
        }
        std::sort(pairs.begin(), pairs.end());
        for (int j = 0; j < n; ++j) {
            if (!uf.isConnected(j, pairs[j].second))
                return false;
        }
        return true;
    }

private:
    std::vector<int> getPrimes(int n)
    {
        std::vector<bool> isPrime(n + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (long long i = 2; i <= n; ++i) {
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
};