#include <algorithm>
#include <cmath>
#include <numbers>
#include <vector>

/**
 * You are given an array points, an integer angle, and your location, where location = [posx, posy]
 * and points[i] = [xi, yi] both denote integral coordinates on the X-Y plane.
 *
 * Initially, you are facing directly east from your position. You cannot move from your position,
 * but you can rotate. In other words, posx and posy cannot be changed. Your field of view in
 * degrees is represented by angle, determining how wide you can see from any given view direction.
 * Let d be the amount in degrees that you rotate counterclockwise. Then, your field of view is the
 * inclusive range of angles [d - angle/2, d + angle/2].
 *
 * You are given an array points, an integer angle, and your location, where location = [posx, posy]
 * and points[i] = [xi, yi] both denote integral coordinates on the X-Y plane.
 *
 * Initially, you are facing directly east from your position. You cannot move from your position,
 * but you can rotate. In other words, posx and posy cannot be changed. Your field of view in
 * degrees is represented by angle, determining how wide you can see from any given view direction.
 * Let d be the amount in degrees that you rotate counterclockwise. Then, your field of view is the
 * inclusive range of angles [d - angle/2, d + angle/2].
 *
 * You can see some set of points if, for each point, the angle formed by the point, your position,
 * and the immediate east direction from your position is in your field of view.
 *
 * There can be multiple points at one coordinate. There may be points at your location, and you can
 * always see these points regardless of your rotation. Points do not obstruct your vision to other
 * points.
 *
 * Return the maximum number of points you can see.
 *
 * ! 1 <= points.length <= 10^5
 * ! points[i].length == 2
 * ! location.length == 2
 * ! 0 <= angle < 360
 * ! 0 <= posx, posy, xi, yi <= 100
 */

class Solution {
public:
    int visiblePoints(std::vector<std::vector<int>>& points, int angle, std::vector<int>& location)
    {
        const int x0 = location[0];
        const int y0 = location[1];
        std::vector<double> radians;
        int same = 0;
        for (const auto& point : points) {
            const int dx = point[0] - x0;
            const int dy = point[1] - y0;
            if (dx == 0 && dy == 0) {
                same++;
                continue;
            }
            const double radian = std::atan2(dy, dx); // [-pi, pi]
            radians.push_back(radian + std::numbers::pi);
        }
        std::sort(radians.begin(), radians.end());
        const int n = radians.size();
        for (int i = 0; i < n; ++i) {
            radians.push_back(radians[i] + 2 * std::numbers::pi);
        }
        const double limit = angle * std::numbers::pi / 180;
        int maxCount = 0;
        for (int i = 0, j = 0; i < 2 * n; ++i) {
            while (j < 2 * n && radians[j] - radians[i] <= limit) {
                j++;
            }
            maxCount = std::max(maxCount, j - i);
        }
        return maxCount + same;
    }
};