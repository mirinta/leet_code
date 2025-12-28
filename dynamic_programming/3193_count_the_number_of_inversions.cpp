#include <cstring>
#include <map>
#include <vector>

/**
 * You are given an integer n and a 2D array requirements, where requirements[i] = [endi, cnti]
 * represents the end index and the inversion count of each requirement.
 *
 * A pair of indices (i, j) from an integer array nums is called an inversion if:
 *
 * - i < j and nums[i] > nums[j]
 *
 * Return the number of permutations perm of [0, 1, 2, ..., n - 1] such that for all
 * requirements[i], perm[0..endi] has exactly cnti inversions.
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * ! 2 <= n <= 300
 * ! 1 <= requirements.length <= n
 * ! requirements[i] = [endi, cnti]
 * ! 0 <= endi <= n - 1
 * ! 0 <= cnti <= 400
 * ! The input is generated such that there is at least one i such that endi == n - 1.
 * ! The input is generated such that all endi are unique.
 */

class Solution {
public:
    int numberOfPermutations(int n, std::vector<std::vector<int>>& requirements)
    {
        // consider this is a 1-indexed problem
        // dp[i][j] = num of perms made of [1,...,i] with exactly j inversions
        // adding integer i to a permutation made of [1,...,i-1]:
        // - adding i to the end, inversion += 0
        // - adding i to the second last position, inversions += 1
        // - adding i to the third last position, inversions += 2
        // ...
        // - adding i to the front, inversion += i-1
        // therefore,
        // dp[i][j] = dp[i-1][j] + dp[i-1][j-1] + ... + dp[i-1][j-(i-1)]
        std::map<long long, long long> map;
        for (const auto& r : requirements) {
            map[r[0] + 1] = r[1];
        }
        long long dp[301][401];
        std::memset(&dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (long long i = 1, lower = 0; i <= n; ++i) {
            if (map.find(i) != map.end()) {
                lower = map[i];
            }
            // it is guaranteed that map contains end_point = n
            // i.e., map.lower_bound(i) != map.end() is always true
            const long long upper = map.lower_bound(i)->second;
            for (long long j = lower; j <= upper; ++j) {
                for (long long k = 0; k <= std::min(j, i - 1); ++k) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % kMod;
                }
            }
            if (map.upper_bound(i) == map.end())
                // the remaining n-i integers can be placed anywhere after i
                return dp[i][lower] * factorial(n - i) % kMod;
        }
        return 0;
    }

private:
    static constexpr long long kMod = 1e9 + 7;

    long long factorial(long long n)
    {
        long long result = 1;
        for (long long i = 1; i <= n; ++i) {
            result = result * i % kMod;
        }
        return result;
    }
};
