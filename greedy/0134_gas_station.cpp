#include <vector>

/**
 * There are n gas stations along a circular route, where the amount of gas at the ith station is
 * gas[i].
 *
 * You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from the ith
 * station to its next (i + 1)th station. You begin the journey with an empty tank at one of the gas
 * stations.
 *
 * Given two integer arrays gas and cost, return the starting gas station's index if you can travel
 * around the circuit once in the clockwise direction, otherwise return -1. If there exists a
 * solution, it is guaranteed to be unique.
 *
 * ! n == gas.length == cost.length
 * ! 1 <= n <= 10^5
 * ! 0 <= gas[i], cost[i] <= 10^4
 */

class Solution {
public:
    int canCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost)
    {
        return approach2(gas, cost);
    }

private:
    // Simplified version of approach1, time O(N), space O(1)
    int approach2(const std::vector<int>& gas, const std::vector<int>& cost)
    {
        const int n = gas.size();
        int tank = 0;
        for (int i = 0; i < n; ++i) {
            tank += gas[i] - cost[i];
        }
        if (tank < 0)
            return -1;

        tank = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            tank += gas[i] - cost[i];
            if (tank < 0) {
                tank = 0;
                result = i + 1;
            }
        }
        return result;
    }

    // Greedy, time O(N), space O(1)
    int approach1(const std::vector<int>& gas, const std::vector<int>& cost)
    {
        const int n = gas.size();
        int totalGas = 0;
        int totalCost = 0;
        for (int i = 0; i < n; ++i) {
            totalGas += gas[i];
            totalCost += cost[i];
        }
        if (totalGas < totalCost)
            return -1;

        for (int start = 0, attempts = 0; attempts < n; ++attempts) {
            // Suppose we can't complete the circular trip starting from A,
            // and B is the furthest position we can reach.
            // Then, any starting position between A and B (inclusive) can't complete trip.
            // Thus, our new attempt starts from B+1.
            const auto [canComplete, furthest] = check(start, gas, cost);
            if (canComplete)
                return start;

            start = (furthest + 1) % n;
        }
        return -1;
    }

    // Given a starting position "start", check if we can complete the circular trip (from "start"
    // to "start"). If we can't complete the trip, return the furthest position we can reach.
    std::pair<bool, int> check(int start, const std::vector<int>& gas, const std::vector<int>& cost)
    {
        const int n = gas.size();
        int tank = gas[start];
        int current = start;
        while (tank >= cost[current]) {
            tank -= cost[current];
            current = (current + 1) % n;
            if (current % n == start)
                return {true, current};

            tank += gas[current];
        }
        return {false, current};
    }
};