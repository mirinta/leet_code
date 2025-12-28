#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array candies. Each element in the array denotes a pile of
 * candies of size candies[i]. You can divide each pile into any number of sub piles, but you cannot
 * merge two piles together.
 *
 * You are also given an integer k. You should allocate piles of candies to k children such that
 * each child gets the same number of candies. Each child can take at most one pile of candies and
 * some piles of candies may go unused.
 *
 * Return the maximum number of candies each child can get.
 *
 * ! 1 <= candies.length <= 10^5
 * ! 1 <= candies[i] <= 10^7
 * ! 1 <= k <= 10^12
 */

class Solution {
public:
    int maximumCandies(std::vector<int>& candies, long long k)
    {
        int lo = 0;
        int hi = *std::max_element(candies.begin(), candies.end());
        while (lo < hi) {
            const long long mid = hi - (hi - lo) / 2;
            if (isValid(mid, candies, k)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    bool isValid(long long limit, const std::vector<int>& candies, long long k)
    {
        for (const auto& val : candies) {
            k -= val / limit;
            if (k <= 0)
                return true;
        }
        return false;
    }
};