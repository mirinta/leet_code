#include <queue>
#include <tuple>
#include <vector>

/**
 * Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an
 * integer k, return the k closest points to the origin (0, 0).
 *
 * The distance between two points on the X-Y plane is the Euclidean distance (i.e., √(x1 - x2)2 +
 * (y1 - y2)2).
 *
 * You may return the answer in any order. The answer is guaranteed to be unique (except for the
 * order that it is in).
 *
 * ! 1 <= k <= points.length <= 10^4
 * ! -10^4 < xi, yi < 10^4
 */

class Solution {
public:
    std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k)
    {
        // max heap
        auto comp = [](const auto& t1, const auto& t2) -> bool { return std::get<0>(t1) < std::get<0>(t2); };
        using Tuple = std::tuple<long, int, int>;
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comp)> pq(comp);
        for (const auto& point : points) {
            pq.emplace(point[0] * point[0] + point[1] * point[1], point[0], point[1]);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<std::vector<int>> result(std::min<size_t>(k, pq.size()), std::vector<int>(2, 0));
        for (int i = result.size() - 1; i >= 0; --i) {
            const auto [_, x, y] = pq.top();
            pq.pop();
            result[i][0] = x;
            result[i][1] = y;
        }
        return result;
    }
};
