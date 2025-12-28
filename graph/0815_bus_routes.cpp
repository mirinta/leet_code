#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given an array routes representing bus routes where routes[i] is a bus route that the ith
 * bus repeats forever.
 *
 * - For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 ->
 * 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
 *
 * You will start at the bus stop source (You are not on any bus initially), and you want to go to
 * the bus stop target. You can travel between bus stops by buses only.
 *
 * Return the least number of buses you must take to travel from source to target. Return -1 if it
 * is not possible.
 *
 * ! 1 <= routes.length <= 500.
 * ! 1 <= routes[i].length <= 10^5
 * ! All the values of routes[i] are unique.
 * ! sum(routes[i].length) <= 10^5
 * ! 0 <= routes[i][j] < 10^6
 * ! 0 <= source, target < 10^6
 */

class Solution {
public:
    int numBusesToDestination(std::vector<std::vector<int>>& routes, int source, int target)
    {
        if (source == target)
            return 0;

        std::unordered_map<int, std::vector<int>> graph;
        for (int bus = 0; bus < routes.size(); ++bus) {
            for (const auto& station : routes[bus]) {
                graph[station].push_back(bus);
            }
        }
        std::unordered_set<int> visited;
        std::queue<int> queue;
        for (const auto& bus : graph[source]) {
            queue.push(bus);
            visited.insert(bus);
        }
        int result = 0;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto bus = queue.front();
                queue.pop();
                for (const auto& station : routes[bus]) {
                    if (station == target)
                        return result + 1;

                    for (const auto& nextBus : graph[station]) {
                        if (!visited.count(nextBus)) {
                            visited.insert(nextBus);
                            queue.push(nextBus);
                        }
                    }
                }
            }
            result++;
        }
        return -1;
    }
};