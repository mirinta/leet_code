#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array stations of length n, where stations[i] represents the
 * number of power stations in the ith city.
 *
 * Each power station can provide power to every city in a fixed range. In other words, if the range
 * is denoted by r, then a power station at city i can provide power to all cities j such that |i -
 * j| <= r and 0 <= i, j <= n - 1.
 *
 *
 * - Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
 *
 * The power of a city is the total number of power stations it is being provided power from.
 *
 * The government has sanctioned building k more power stations, each of which can be built in any
 * city, and have the same range as the pre-existing ones.
 *
 * Given the two integers r and k, return the maximum possible minimum power of a city, if the
 * additional power stations are built optimally.
 *
 * Note that you can build the k power stations in multiple cities.
 *
 * ! n == stations.length
 * ! 1 <= n <= 10^5
 * ! 0 <= stations[i] <= 10^5
 * ! 0 <= r <= n - 1
 * ! 0 <= k <= 10^9
 */

class Solution {
public:
    long long maxPower(std::vector<int>& stations, int r, int k)
    {
        long long lo = 0;
        long long hi = LLONG_MAX;
        while (lo < hi) {
            const long long mid = hi - (hi - lo) / 2;
            if (isValid(mid, stations, r, k)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(long long min, std::vector<int> stations, int r, int k)
    {
        // power[i-1] = stations[i-r-1] + ... + stations[i-1] + ... + stations[i+r-1]
        // power[i] = power[i-1] - stations[i-r-1] + stations[i+r]
        const int n = stations.size();
        long long power = 0;
        for (int i = 0; i < std::min(r, n); ++i) {
            power += stations[i];
        }
        for (int i = 0; i < n; ++i) {
            if (i + r < n) {
                power += stations[i + r];
            }
            if (i - r - 1 >= 0) {
                power -= stations[i - r - 1];
            }
            if (power >= min)
                continue;

            const long long extra = min - power;
            if (k < extra)
                return false;

            k -= extra;
            power += extra;
            stations[std::min(n - 1, i + r)] += extra;
        }
        return true;
    }
};