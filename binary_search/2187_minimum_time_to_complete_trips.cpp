#include <vector>

/**
 * You are given an array time where time[i] denotes the time taken by the ith bus to complete one
 * trip.
 *
 * Each bus can make multiple trips successively; that is, the next trip can start immediately after
 * completing the current trip. Also, each bus operates independently; that is, the trips of one bus
 * do not influence the trips of any other bus.
 *
 * You are also given an integer totalTrips, which denotes the number of trips all buses should make
 * in total. Return the minimum time required for all buses to complete at least totalTrips trips.
 *
 * ! 1 <= time.length <= 10^5
 * ! 1 <= time[i], totalTrips <= 10^7
 */

class Solution {
public:
    long long minimumTime(std::vector<int>& time, int totalTrips)
    {
        long long lo = 1;
        long long hi = LLONG_MAX;
        while (lo < hi) {
            const long long mid = lo + (hi - lo) / 2;
            if (isValid(mid, time, totalTrips)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(long long timeLimit, const std::vector<int>& time, long long totalTrips)
    {
        long long sum = 0;
        for (const auto& t : time) {
            sum += timeLimit / t;
            if (sum >= totalTrips)
                return true;
        }
        return false;
    }
};