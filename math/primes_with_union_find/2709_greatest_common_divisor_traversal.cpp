#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums, and you are allowed to traverse between its
 * indices. You can traverse between index i and index j, i != j, if and only if gcd(nums[i],
 * nums[j]) > 1, where gcd is the greatest common divisor.
 *
 * Your task is to determine if for every pair of indices i and j in nums, where i < j, there exists
 * a sequence of traversals that can take us from i to j.
 *
 * Return true if it is possible to traverse between all such pairs of indices, or false otherwise.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
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

        if (size[rootP] < size[rootQ]) {
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
    bool canTraverseAllPairs(std::vector<int>& nums)
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
        for (int i = 1; i < n; ++i) {
            if (!uf.isConnected(0, i))
                return false;
        }
        return true;
    }

private:
    // return all primes in the range [1, n]
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

    std::vector<int> getPrimeFactors(int n, const std::vector<int>& primes)
    {
        std::vector<int> result;
        for (const auto& p : primes) {
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