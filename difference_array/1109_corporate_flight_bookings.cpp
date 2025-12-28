#include <vector>

/**
 * There are n flights that are labeled from 1 to n.
 *
 * You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi]
 * represents a booking for flights firsti through lasti (inclusive) with seatsi seats reserved for
 * each flight in the range.
 *
 * Return an array answer of length n, where answer[i] is the total number of seats reserved for
 * flight i.
 *
 * ! 1 <= n <= 2 * 10^4
 * ! 1 <= bookings.length <= 2 * 10^4
 * ! bookings[i].length == 3
 * ! 1 <= firsti <= lasti <= n
 * ! 1 <= seatsi <= 10^4
 */

class Solution {
public:
    std::vector<int> corpFlightBookings(std::vector<std::vector<int>>& bookings, int n)
    {
        // seats[i] = total num of seats reserved for flight i
        // diff[i] = seats[i] - seats[i-1], diff[0] = seats[i]
        std::vector<int> diff(n, 0);
        for (const auto& booking : bookings) {
            const int from = booking[0] - 1; // to 0-indexed
            const int to = booking[1] - 1;   // to 0-indexed
            const int seats = booking[2];
            diff[from] += seats;
            if (to + 1 < n) {
                diff[to + 1] -= seats;
            }
        }
        for (int i = 1; i < n; ++i) {
            diff[i] += diff[i - 1];
        }
        return diff;
    }
};