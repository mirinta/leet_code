#include <algorithm>
#include <string>
#include <vector>

/**
 * Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes
 * difference between any two time-points in the list.
 *
 * ! 2 <= timePoints.length <= 2 * 10^4
 * ! timePoints[i] is in the format "HH:MM".
 */

class Solution {
public:
    int findMinDifference(std::vector<std::string>& timePoints)
    {
        const int n = timePoints.size();
        std::vector<int> v;
        v.reserve(n);
        for (const auto& s : timePoints) {
            v.push_back(std::stoi(s.substr(0, 2)) * 60 + std::stoi(s.substr(3, 2)));
        }
        std::sort(v.begin(), v.end());
        int result = INT_MAX;
        for (int i = 1; i < n; ++i) {
            result = std::min(result, v[i] - v[i - 1]);
        }
        result = std::min(result, 24 * 60 - v.back() + v.front());
        return result;
    }
};