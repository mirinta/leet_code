#include <string>
#include <vector>

/**
 * You are given two 0-indexed strings source and target, both of length n and consisting of
 * lowercase English letters. You are also given two 0-indexed character arrays original and
 * changed, and an integer array cost, where cost[i] represents the cost of changing the character
 * original[i] to the character changed[i].
 *
 * You start with the string source. In one operation, you can pick a character x from the string
 * and change it to the character y at a cost of z if there exists any index j such that cost[j] ==
 * z, original[j] == x, and changed[j] == y.
 *
 * Return the minimum cost to convert the string source to the string target using any number of
 * operations. If it is impossible to convert source to target, return -1.
 *
 * Note that there may exist indices i, j such that original[j] == original[i] and changed[j] ==
 * changed[i].
 *
 * ! 1 <= source.length == target.length <= 10^5
 * ! source, target consist of lowercase English letters.
 * ! 1 <= cost.length == original.length == changed.length <= 2000
 * ! original[i], changed[i] are lowercase English letters.
 * ! 1 <= cost[i] <= 10^6
 * ! original[i] != changed[i]
 */

class Solution {
public:
    long long minimumCost(std::string source,
                          std::string target,
                          std::vector<char>& original,
                          std::vector<char>& changed,
                          std::vector<int>& cost)
    {
        const int n = source.size();
        const auto minDist = floyd(original, changed, cost);
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            const int from = source[i] - 'a';
            const int to = target[i] - 'a';
            if (minDist[from][to] == LLONG_MAX)
                return -1;

            result += minDist[from][to];
        }
        return result;
    }

private:
    std::vector<std::vector<long long>>
        floyd(const std::vector<char>& original, const std::vector<char>& changed, const std::vector<int>& cost)
    {
        std::vector<std::vector<long long>> minDist(26, std::vector<long long>(26, LLONG_MAX));
        for (int i = 0; i < 26; ++i) {
            minDist[i][i] = 0;
        }
        for (int i = 0; i < original.size(); ++i) {
            const int from = original[i] - 'a';
            const int to = changed[i] - 'a';
            minDist[from][to] = std::min<long long>(minDist[from][to], cost[i]);
        }
        for (int k = 0; k < 26; ++k) {
            for (int i = 0; i < 26; ++i) {
                if (minDist[i][k] == LLONG_MAX)
                    continue;

                for (int j = 0; j < 26; ++j) {
                    if (minDist[k][j] == LLONG_MAX)
                        continue;

                    minDist[i][j] = std::min(minDist[i][j], minDist[i][k] + minDist[k][j]);
                }
            }
        }
        return minDist;
    }
};