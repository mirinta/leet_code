#include <numeric>
#include <vector>

/**
 * You have n computers. You are given the integer n and a 0-indexed integer array batteries where
 * the ith battery can run a computer for batteries[i] minutes. You are interested in running all n
 * computers simultaneously using the given batteries.
 *
 *
 * Initially, you can insert at most one battery into each computer. After that and at any integer
 * time moment, you can remove a battery from a computer and insert another battery any number of
 * times. The inserted battery can be a totally new battery or a battery from another computer. You
 * may assume that the removing and inserting processes take no time.
 *
 * Note that the batteries cannot be recharged.
 *
 * Return the maximum number of minutes you can run all the n computers simultaneously.
 *
 * ! 1 <= n <= batteries.length <= 10^5
 * ! 1 <= batteries[i] <= 10^9
 */

class Solution {
public:
    long long maxRunTime(int n, std::vector<int>& batteries)
    {
        long long lo = 0;
        long long hi = std::accumulate(batteries.begin(), batteries.end(), 0LL) / n;
        while (lo <= hi) {
            const long long mid = lo + (hi - lo) / 2;
            if (isValid(mid, n, batteries)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(long long time, int n, const std::vector<int>& batteries)
    {
        long long sum = 0;
        long long need = time * n;
        for (const long long& val : batteries) {
            sum += std::min(val, time);
            if (sum >= need)
                return true;
        }
        return false;
    }
};