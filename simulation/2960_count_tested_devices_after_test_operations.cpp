#include <vector>

/**
 * You are given a 0-indexed integer array batteryPercentages having length n, denoting the battery
 * percentages of n 0-indexed devices.
 *
 * Your task is to test each device i in order from 0 to n - 1, by performing the following test
 * operations:
 *
 * - If batteryPercentages[i] is greater than 0:
 *
 *   - Increment the count of tested devices.
 *
 *   - Decrease the battery percentage of all devices with indices j in the range [i + 1, n - 1] by
 * 1, ensuring their battery percentage never goes below 0, i.e, batteryPercentages[j] = max(0,
 * batteryPercentages[j] - 1).
 *
 *   - Move to the next device.
 *
 * - Otherwise, move to the next device without performing any test.
 *
 * Return an integer denoting the number of devices that will be tested after performing the test
 * operations in order.
 *
 * ! 1 <= n == batteryPercentages.length <= 100
 * ! 0 <= batteryPercentages[i] <= 100
 */

class Solution {
public:
    int countTestedDevices(std::vector<int>& batteryPercentages)
    {
        return approach2(batteryPercentages);
    }

private:
    // time O(N), space O(1)
    int approach2(std::vector<int>& batteryPercentages)
    {
        int result = 0;
        int decrement = 0;
        for (const auto& val : batteryPercentages) {
            if (val - decrement > 0) {
                result++;
                decrement++;
            }
        }
        return result;
    }

    // time O(N^2), space O(1)
    int approach1(std::vector<int>& batteryPercentages)
    {
        const int n = batteryPercentages.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            if (batteryPercentages[i] <= 0)
                continue;

            result++;
            for (int j = i + 1; j < n; ++j) {
                batteryPercentages[j] = std::max(0, batteryPercentages[j] - 1);
            }
        }
        return result;
    }
};