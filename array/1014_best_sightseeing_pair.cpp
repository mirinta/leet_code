#include <vector>

/**
 * You are given an integer array values where values[i] represents the value of the ith sightseeing
 * spot. Two sightseeing spots i and j have a distance j - i between them.
 *
 * The score of a pair (i < j) of sightseeing spots is values[i] + values[j] + i - j: the sum of the
 * values of the sightseeing spots, minus the distance between them.
 *
 * Return the maximum score of a pair of sightseeing spots.
 *
 * ! 2 <= values.length <= 5 * 10^4
 * ! 1 <= values[i] <= 1000
 */

class Solution {
public:
    int maxScoreSightseeingPair(std::vector<int>& values)
    {
        const int n = values.size();
        int prevMax = values[0]; // values[i] + i
        int result = INT_MIN;
        for (int j = 1; j < n; ++j) {
            result = std::max(result, values[j] - j + prevMax);
            prevMax = std::max(prevMax, values[j] + j);
        }
        return result;
    }
};
