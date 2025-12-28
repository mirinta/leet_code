#include <map>
#include <set>
#include <vector>

/**
 * A city's skyline is the outer contour of the silhouette formed by all the buildings in that city
 * when viewed from a distance. Given the locations and heights of all the buildings, return the
 * skyline formed by these buildings collectively.
 *
 * The geometric information of each building is given in the array buildings where buildings[i] =
 * [left_i, right_i, height_i]:
 *
 * - left_i is the x coordinate of the left edge of the ith building.
 *
 * - right_i is the x coordinate of the right edge of the ith building.
 *
 * - height_i is the height of the ith building.
 *
 * You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at
 * height 0.
 *
 * The skyline should be represented as a list of "key points" sorted by their x-coordinate in the
 * form [[x1,y1],[x2,y2],...]. Each key point is the left endpoint of some horizontal segment in the
 * skyline except the last point in the list, which always has a y-coordinate 0 and is used to mark
 * the skyline's termination where the rightmost building ends. Any ground between the leftmost and
 * rightmost buildings should be part of the skyline's contour.
 *
 * Note: There must be no consecutive horizontal lines of equal height in the output skyline. For
 * instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not acceptable; the three lines of height
 * 5 should be merged into one in the final output as such: [...,[2 3],[4 5],[12 7],...].
 *
 * ! 1 <= buildings.length <= 10^4
 * ! 0 <= left_i < right_i <= 2^31 - 1
 * ! 1 <= height_i <= 2^31 - 1
 * ! buildings are sorted by left_i in non-decreasing order.
 */

class Solution {
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings)
    {
        std::map<int, std::vector<std::pair<int, int>>> map; // <pos, {<height, flag>}>
        for (const auto& building : buildings) {
            const auto& left = building[0];
            const auto& right = building[1];
            const auto& height = building[2];
            map[left].emplace_back(height, 1);
            map[right].emplace_back(height, -1);
        }
        std::multiset<int> set;
        std::vector<std::vector<int>> result;
        for (const auto& [pos, pairs] : map) {
            for (const auto& [height, flag] : pairs) {
                if (flag == 1) {
                    set.insert(height);
                } else {
                    set.erase(set.find(height));
                }
            }
            const int max = set.empty() ? 0 : *set.rbegin();
            if (result.empty() || result.back()[1] != max) {
                result.push_back({pos, max});
            }
        }
        return result;
    }
};
