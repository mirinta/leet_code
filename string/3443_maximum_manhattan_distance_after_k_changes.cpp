#include <string>

/**
 * You are given a string s consisting of the characters 'N', 'S', 'E', and 'W', where s[i]
 * indicates movements in an infinite grid:
 *
 * - 'N' : Move north by 1 unit.
 *
 * - 'S' : Move south by 1 unit.
 *
 * - 'E' : Move east by 1 unit.
 *
 * - 'W' : Move west by 1 unit.
 *
 * Initially, you are at the origin (0, 0). You can change at most k characters to any of the four
 * directions.
 *
 * Find the maximum Manhattan distance from the origin that can be achieved at any time while
 * performing the movements in order.
 *
 * The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
 *
 * ! 1 <= s.length <= 10^5
 * ! 0 <= k <= s.length
 * ! s consists of only 'N', 'S', 'E', and 'W'.
 */

class Solution
{
public:
    int maxDistance(std::string s, int k)
    {
        int north = 0;
        int south = 0;
        int east = 0;
        int west = 0;
        int result = 0;
        for (const auto& c : s) {
            if (c == 'N') {
                north++;
            } else if (c == 'S') {
                south++;
            } else if (c == 'E') {
                east++;
            } else {
                west++;
            }
            const int count1 = std::min({north, south, k});
            const int count2 = std::min({east, west, k - count1});
            const int dist =
                std::abs(north - south) + std::abs(east - west) + 2 * (count1 + count2);
            result = std::max(result, dist);
        }
        return result;
    }
};