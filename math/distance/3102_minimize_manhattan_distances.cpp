#include <set>
#include <vector>

/**
 * You are given a 0-indexed array points representing integer coordinates of some points on a 2D
 * plane, where points[i] = [xi, yi].
 *
 * The distance between two points is defined as their Manhattan distance.
 *
 * Return the minimum possible value for maximum distance between any two points by removing exactly
 * one point.
 *
 * ! 3 <= points.length <= 10^5
 * ! points[i].length == 2
 * ! 1 <= points[i][0], points[i][1] <= 10^8
 */

class Solution {
public:
    int minimumDistance(std::vector<std::vector<int>>& points)
    {
        std::multiset<int> set1; // xi+yi
        std::multiset<int> set2; // xi-yi
        std::multiset<int> set3; // -xi+yi
        std::multiset<int> set4; // -xi-yi
        for (const auto& point : points) {
            const auto& x = point[0];
            const auto& y = point[1];
            set1.insert(x + y);
            set2.insert(x - y);
            set3.insert(-x + y);
            set4.insert(-x - y);
        }
        int result = INT_MAX;
        for (const auto& point : points) {
            const auto& x = point[0];
            const auto& y = point[1];
            set1.erase(set1.find(x + y));
            set2.erase(set2.find(x - y));
            set3.erase(set3.find(-x + y));
            set4.erase(set4.find(-x - y));
            int maxDist = 0;
            maxDist = std::max(maxDist, *set1.rbegin() - *set1.begin());
            maxDist = std::max(maxDist, *set2.rbegin() - *set2.begin());
            maxDist = std::max(maxDist, *set3.rbegin() - *set3.begin());
            maxDist = std::max(maxDist, *set4.rbegin() - *set4.begin());
            result = std::min(result, maxDist);
            set1.insert(x + y);
            set2.insert(x - y);
            set3.insert(-x + y);
            set4.insert(-x - y);
        }
        return result;
    }
};