#include <vector>

/**
 * You are given a 0-indexed 2D array variables where variables[i] = [ai, bi, ci, mi], and an
 * integer target.
 *
 * An index i is good if the following formula holds:
 *
 * - 0 <= i < variables.length
 *
 * - ((ai^bi % 10)^ci) % mi == target
 *
 * Return an array consisting of good indices in any order.
 *
 * ! 1 <= variables.length <= 100
 * ! variables[i] == [ai, bi, ci, mi]
 * ! 1 <= ai, bi, ci, mi <= 10^3
 * ! 0 <= target <= 10^3
 */

class Solution {
public:
    std::vector<int> getGoodIndices(std::vector<std::vector<int>>& variables, int target)
    {
        std::vector<int> result;
        for (int i = 0; i < variables.size(); ++i) {
            const auto& a = variables[i][0];
            const auto& b = variables[i][1];
            const auto& c = variables[i][2];
            const auto& m = variables[i][3];
            if (powmod(powmod(a, b, 10), c, m) == target) {
                result.push_back(i);
            }
        }
        return result;
    }

private:
    long long powmod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a % mod;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};