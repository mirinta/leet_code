#include <cmath>
#include <vector>

/**
 * You are given an integer array ranks representing the ranks of some mechanics. ranksi is the rank
 * of the ith mechanic. A mechanic with a rank r can repair n cars in r * n2 minutes.
 *
 * You are also given an integer cars representing the total number of cars waiting in the garage to
 * be repaired.
 *
 * Return the minimum time taken to repair all the cars.
 *
 * Note: All the mechanics can repair the cars simultaneously.
 *
 * ! 1 <= ranks.length <= 10^5
 * ! 1 <= ranks[i] <= 100
 * ! 1 <= cars <= 10^6
 */

class Solution {
public:
    long long repairCars(std::vector<int>& ranks, int cars)
    {
        long long lo = 1;
        long long hi = 1LL * ranks.back() * cars * cars;
        while (lo < hi) {
            const long long mid = lo + (hi - lo) / 2;
            if (isValid(mid, ranks, cars)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(long long time, const std::vector<int>& ranks, long long cars)
    {
        long long count = 0;
        for (const auto& r : ranks) {
            count += std::sqrt(time / r);
            if (count >= cars)
                return true;
        }
        return false;
    }
};
