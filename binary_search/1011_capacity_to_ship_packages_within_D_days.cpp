#include <algorithm>
#include <numeric>
#include <vector>

/**
 * A conveyor belt has packages that must be shipped from one port to another within days days.
 *
 * The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with
 * packages on the conveyor belt (in the order given by weights). We may not load more weight than
 * the maximum weight capacity of the ship.
 *
 * Return the least weight capacity of the ship that will result in all the packages on the conveyor
 * belt being shipped within days days.
 *
 * ! 1 <= days <= weights.length <= 5 * 10^4
 * ! 1 <= weights[i] <= 500
 */

class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days)
    {
        int min = *std::max_element(weights.begin(), weights.end());
        int max = std::accumulate(weights.begin(), weights.end(), 0);
        while (min < max) {
            const int capacity = min + (max - min) / 2;
            if (isValid(capacity, weights, days)) {
                max = capacity;
            } else {
                min = capacity + 1;
            }
        }
        return min;
    }

private:
    bool isValid(int capacity, const std::vector<int>& weights, int days)
    {
        int time = 1;
        int sum = 0;
        for (const auto& val : weights) {
            if (val > capacity)
                return false;

            sum += val;
            if (sum > capacity) {
                sum = val;
                time++;
            }
            if (time > days)
                return false;
        }
        return true;
    }
};