#include <unordered_map>
#include <vector>

/**
 * You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find
 * the number of different ways you can place positive integers into an array of size ni such that
 * the product of the integers is ki. As the number of ways may be too large, the answer to the ith
 * query is the number of ways modulo 109 + 7.
 *
 * Return an integer array answer where answer.length == queries.length, and answer[i] is the answer
 * to the ith query.
 *
 * ! 1 <= queries.length <= 10^4
 * ! 1 <= ni, ki <= 10^4
 */

class Solution {
public:
    std::vector<int> waysToFillArray(std::vector<std::vector<int>>& queries)
    {
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            const int n = query[0];
            const int k = query[1];
            result.push_back(helper(n, k));
        }
        return result;
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // num of different ways to place positive integers into an array of size n
    // such that the product of the integers is k
    int helper(int n, int k)
    {
        const auto map = getPrimeFactors(k);
        long long result = 1;
        for (const auto& [factor, count] : map) {
            result = result * combination(count + n - 1, n - 1) % kMod;
        }
        return result;
    }

    std::unordered_map<int, int> getPrimeFactors(int n)
    {
        std::unordered_map<int, int> result;
        for (int i = 2; i * i <= n; ++i) {
            while (n % i == 0) {
                result[i]++;
                n /= i;
            }
        }
        if (n != 1) {
            result[n]++;
        }
        return result;
    }

    int combination(int m, int n)
    {
        static std::unordered_map<int, std::unordered_map<int, int>> memo;
        if (m == n || n == 0)
            return 1;

        if (memo.count(m) && memo[m].count(n))
            return memo[m][n];

        if (memo.count(m) && memo[m].count(m - n))
            return memo[m][m - n];

        return memo[m][n] = (combination(m - 1, n) + combination(m - 1, n - 1)) % kMod;
    }
};