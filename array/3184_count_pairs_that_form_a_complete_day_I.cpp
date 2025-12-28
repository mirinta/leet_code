#include <unordered_map>
#include <vector>

/**
 * Given an integer array hours representing times in hours, return an integer denoting the number
 * of pairs i, j where i < j and hours[i] + hours[j] forms a complete day.
 *
 * A complete day is defined as a time duration that is an exact multiple of 24 hours.
 *
 * For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and so on.
 *
 * ! 1 <= hours.length <= 100
 * ! 1 <= hours[i] <= 10^9
 */

class Solution {
public:
    int countCompleteDayPairs(std::vector<int>& hours)
    {
        const int n = hours.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if ((hours[i] + hours[j]) % 24 == 0) {
                    result++;
                }
            }
        }
        return result;
    }
};