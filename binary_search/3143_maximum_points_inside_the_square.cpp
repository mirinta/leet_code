#include <string>
#include <vector>

/**
 * You are given a 2D array points and a string s where, points[i] represents the coordinates of
 * point i, and s[i] represents the tag of point i.
 *
 * A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and
 * does not contain two points with the same tag.
 *
 * Return the maximum number of points contained in a valid square.
 *
 * Note:
 *
 * A point is considered to be inside the square if it lies on or within the square's boundaries.
 * The side length of the square can be zero.
 *
 * ! 1 <= s.length, points.length <= 10^5
 * ! points[i].length == 2
 * ! -10^9 <= points[i][0], points[i][1] <= 10^9
 * ! s.length == points.length
 * ! points consists of distinct coordinates.
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    int maxPointsInsideSquare(std::vector<std::vector<int>>& points, std::string s)
    {
        int maxHalfLength = 0;
        for (const auto& p : points) {
            maxHalfLength = std::max({maxHalfLength, std::abs(p[0]), std::abs(p[1])});
        }
        int lo = 0;
        int hi = maxHalfLength;
        int result = 0;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(result, mid, points, s)) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return result;
    }

private:
    bool isValid(int& result, int halfLength, const std::vector<std::vector<int>>& points, const std::string& s)
    {
        const int n = s.size();
        int mask = 0;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            const int id = s[i] - 'a';
            if (std::abs(points[i][0]) > halfLength || std::abs(points[i][1]) > halfLength)
                continue;

            if (mask >> id & 1)
                return false;

            count++;
            mask |= 1 << id;
        }
        result = std::max(result, count);
        return true;
    }
};