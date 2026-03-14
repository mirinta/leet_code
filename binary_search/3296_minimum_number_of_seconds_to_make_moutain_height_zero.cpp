#include <algorithm>
#include <cmath>
#include <vector>

/**
 * You are given an integer mountainHeight denoting the height of a mountain.
 *
 * You are also given an integer array workerTimes representing the work time of workers in seconds.
 *
 * The workers work simultaneously to reduce the height of the mountain. For worker i:
 *
 * - To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x
 * seconds. For example:
 *
 *     - To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
 *
 *     - To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.
 *
 * Return an integer representing the minimum number of seconds required for the workers to make the height of the
 * mountain 0.
 *
 * ! 1 <= mountainHeight <= 10^5
 * ! 1 <= workerTimes.length <= 10^4
 * ! 1 <= workerTimes[i] <= 10^6
 */

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, std::vector<int>& workerTimes)
    {
        const long long max = *std::max_element(workerTimes.begin(), workerTimes.end());
        long long lo = 0;
        long long hi = max * (1 + mountainHeight) * mountainHeight / 2;
        while (lo < hi) {
            const auto mid = lo + (hi - lo) / 2;
            if (isValid(mid, mountainHeight, workerTimes)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return hi;
    }

private:
    bool isValid(long long max, long long mountainHeight, const std::vector<int>& workerTimes)
    {
        long long total = 0;
        for (const auto& t : workerTimes) {
            total += (std::sqrt(1 + 8.0 * max / t) - 1) / 2.0;
            if (total >= mountainHeight)
                return true;
        }
        return false;
    }
};
