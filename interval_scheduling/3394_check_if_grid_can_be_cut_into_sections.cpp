#include <algorithm>
#include <climits>
#include <vector>

/**
 * You are given an integer n representing the dimensions of an n x n grid, with the origin at the
 * bottom-left corner of the grid. You are also given a 2D array of coordinates rectangles, where
 * rectangles[i] is in the form [startx, starty, endx, endy], representing a rectangle on the grid.
 * Each rectangle is defined as follows:
 *
 * - (startx, starty): The bottom-left corner of the rectangle.
 *
 * - (endx, endy): The top-right corner of the rectangle.
 *
 * Note that the rectangles do not overlap. Your task is to determine if it is possible to make
 * either two horizontal or two vertical cuts on the grid such that:
 *
 * - Each of the three resulting sections formed by the cuts contains at least one rectangle.
 *
 * - Every rectangle belongs to exactly one section.
 *
 * Return true if such cuts can be made; otherwise, return false.
 *
 * ! 3 <= n <= 10^9
 * ! 3 <= rectangles.length <= 10^5
 * ! 0 <= rectangles[i][0] < rectangles[i][2] <= n
 * ! 0 <= rectangles[i][1] < rectangles[i][3] <= n
 * ! No two rectangles overlap.
 */

class Solution {
public:
    bool checkValidCuts(int n, std::vector<std::vector<int>>& rectangles)
    {
        std::vector<std::pair<int, int>> xAxis;
        std::vector<std::pair<int, int>> yAxis;
        for (const auto& rect : rectangles) {
            xAxis.emplace_back(rect[0], rect[2]);
            yAxis.emplace_back(rect[1], rect[3]);
        }
        return check(xAxis) || check(yAxis);
    }

private:
    // check whether the num of non-overlapping intervals >= 3
    int check(std::vector<std::pair<int, int>>& intervals)
    {
        std::sort(intervals.begin(), intervals.end(), [](const auto& p1, const auto& p2) {
            return p1.first == p2.first ? p1.second > p2.second : p1.first < p2.first;
        });
        int count = 0;
        for (int i = 0, end = INT_MIN; i < intervals.size(); ++i) {
            count += intervals[i].first >= end;
            if (count >= 3)
                return true;

            end = std::max(end, intervals[i].second);
        }
        return false;
    }
};
