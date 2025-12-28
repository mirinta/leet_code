#include <algorithm>
#include <vector>

/**
 * You are given two arrays of positive integers, boxes and warehouse, representing the heights of
 * some boxes of unit width and the heights of n rooms in a warehouse respectively. The warehouse's
 * rooms are labelled from 0 to n - 1 from left to right where warehouse[i] (0-indexed) is the
 * height of the ith room.
 *
 * Boxes are put into the warehouse by the following rules:
 *
 * - Boxes cannot be stacked.
 *
 * - You can rearrange the insertion order of the boxes.
 *
 * - Boxes can only be pushed into the warehouse from left to right only.
 *
 * - If the height of some room in the warehouse is less than the height of a box, then that box and
 * all other boxes behind it will be stopped before that room.
 *
 * Return the maximum number of boxes you can put into the warehouse.
 *
 * ! n == warehouse.length
 * ! 1 <= boxes.length, warehouse.length <= 10^5
 * ! 1 <= boxes[i], warehouse[i] <= 10^9
 */

class Solution {
public:
    int maxBoxesInWarehouse(std::vector<int>& boxes, std::vector<int>& warehouse)
    {
        std::sort(boxes.begin(), boxes.end(), std::greater<>());
        int result = 0;
        for (int i = 0, j = 0; i < boxes.size() && j < warehouse.size(); ++i) {
            if (warehouse[j] >= boxes[i]) {
                j++;
                result++;
            }
        }
        return result;
    }
};