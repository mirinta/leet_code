#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array buses of length n, where buses[i] represents the
 * departure time of the ith bus. You are also given a 0-indexed integer array passengers of length
 * m, where passengers[j] represents the arrival time of the jth passenger. All bus departure times
 * are unique. All passenger arrival times are unique.
 *
 * You are given an integer capacity, which represents the maximum number of passengers that can get
 * on each bus.
 *
 * When a passenger arrives, they will wait in line for the next available bus. You can get on a bus
 * that departs at x minutes if you arrive at y minutes where y <= x, and the bus is not full.
 * Passengers with the earliest arrival times get on the bus first.
 *
 * More formally when a bus arrives, either:
 *
 * - If capacity or fewer passengers are waiting for a bus, they will all get on the bus, or
 *
 * - The capacity passengers with the earliest arrival times will get on the bus.
 *
 * Return the latest time you may arrive at the bus station to catch a bus. You cannot arrive at the
 * same time as another passenger.
 *
 * Note: The arrays buses and passengers are not necessarily sorted.
 *
 * ! n == buses.length
 * ! m == passengers.length
 * ! 1 <= n, m, capacity <= 10^5
 * ! 2 <= buses[i], passengers[i] <= 10^9
 * ! Each element in buses is unique.
 * ! Each element in passengers is unique.
 */

class Solution {
public:
    int latestTimeCatchTheBus(std::vector<int>& buses, std::vector<int>& passengers, int capacity)
    {
        std::sort(buses.begin(), buses.end());
        std::sort(passengers.begin(), passengers.end());
        const int n = passengers.size();
        int i = 0;
        int prev = -1;
        int result = 0;
        for (const auto& bus : buses) {
            int remaining = capacity;
            while (i < n && passengers[i] <= bus && remaining > 0) {
                remaining--;
                result = passengers[i] - prev == 1 ? result : passengers[i] - 1;
                prev = passengers[i];
                i++;
            }
            if (remaining > 0 && prev != bus) {
                result = bus;
            }
        }
        return result;
    }
};