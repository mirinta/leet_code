#include <utility>
#include <vector>

/**
 * An axis-aligned rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) is the
 * coordinate of its bottom-left corner, and (x2, y2) is the coordinate of its top-right corner. Its
 * top and bottom edges are parallel to the X-axis, and its left and right edges are parallel to the
 * Y-axis.
 *
 * Two rectangles overlap if the area of their intersection is positive. To be clear, two rectangles
 * that only touch at the corner or edges do not overlap.
 *
 * Given two axis-aligned rectangles rec1 and rec2, return true if they overlap, otherwise return
 * false.
 *
 * ! rec1.length == 4
 * ! rec2.length == 4
 * ! -10^9 <= rec1[i], rec2[i] <= 10^9
 * ! rec1 and rec2 represent a valid rectangle with a non-zero area.
 */

class Solution {
public:
    bool isRectangleOverlap(std::vector<int>& rec1, std::vector<int>& rec2)
    {
        const int width = std::min(rec1[2], rec2[2]) - std::max(rec1[0], rec2[0]);
        const int height = std::min(rec1[3], rec2[3]) - std::max(rec1[1], rec2[1]);
        return width > 0 && height > 0;
    }
};