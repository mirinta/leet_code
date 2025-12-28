#include <algorithm>
#include <array>
#include <vector>

/**
 * There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn
 * around and drive west).
 *
 * You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi,
 * toi] indicates that the ith trip has numPassengersi passengers and the locations to pick them up
 * and drop them off are fromi and toi respectively. The locations are given as the number of
 * kilometers due east from the car's initial location.
 *
 * Return true if it is possible to pick up and drop off all passengers for all the given trips, or
 * false otherwise.
 *
 * ! 1 <= trips.length <= 1000
 * ! trips[i].length == 3
 * ! 1 <= numPassengersi <= 100
 * ! 0 <= fromi < toi <= 1000
 * ! 1 <= capacity <= 10^5
 */

class Solution {
public:
    bool carPooling(std::vector<std::vector<int>>& trips, int capacity)
    {
        return approach2(trips, capacity);
    }

private:
    // Difference array, TC = O(N), SC = O(1)
    bool approach2(const std::vector<std::vector<int>>& trips, int capacity)
    {
        // seats[i] = num of passengers of the ith station
        // given trip = [passengers, from, to]
        // we need to increase seats[from],seats[from+1],...,seats[to-1] by passengers
        // thus, we define our difference array diff[i] = seats[i] - seats[i-1]
        std::array<int, 1001> diff{0};
        std::fill(diff.begin(), diff.end(), 0);
        for (const auto& trip : trips) {
            const int passengers = trip[0];
            const int from = trip[1];
            const int to = trip[2];
            diff[from] += passengers;
            diff[to] -= passengers;
        }
        // restore seats and check seats[i] <= capacity
        for (int i = 0; i < diff.size(); ++i) {
            if (i > 0) {
                diff[i] += diff[i - 1];
            }
            if (diff[i] > capacity)
                return false;
        }
        return true;
    }

    // Sweep line, TC = O(N), SC = O(N)
    bool approach1(const std::vector<std::vector<int>>& trips, int capacity)
    {
        // from0------to0
        //       from1------to1
        // if station i is a "from" station, seats[i] += passengers
        // if station i is a "to" station, seats[i] -= passengers
        std::vector<std::pair<int, int>> timestamps; // <station, +1/-1 * passengers>
        for (const auto& trip : trips) {
            timestamps.emplace_back(trip[1], trip[0]);
            timestamps.emplace_back(trip[2], -trip[0]);
        }
        // if "from" and "to" are the same station, we should process "to" first
        std::sort(timestamps.begin(), timestamps.end(), [](const auto& p1, const auto& p2) {
            return p1.first != p2.first ? p1.first < p2.first : p1.second < p2.second;
        });
        int seats = 0;
        for (const auto& [station, passengers] : timestamps) {
            seats += passengers;
            if (seats > capacity)
                return false;
        }
        return true;
    }
};