#include <unordered_map>
#include <vector>

/**
 * You are given an integer limit and a 2D array queries of size n x 2.
 *
 * There are limit + 1 balls with distinct labels in the range [0, limit]. Initially, all balls are
 * uncolored. For every query in queries that is of the form [x, y], you mark ball x with the color
 * y. After each query, you need to find the number of distinct colors among the balls.
 *
 * Return an array result of length n, where result[i] denotes the number of distinct colors after
 * ith query.
 *
 * Note that when answering a query, lack of a color will not be considered as a color.
 *
 * ! 1 <= limit <= 10^9
 * ! 1 <= n == queries.length <= 10^5
 * ! queries[i].length == 2
 * ! 0 <= queries[i][0] <= limit
 * ! 1 <= queries[i][1] <= 10^9
 */

class Solution {
public:
    std::vector<int> queryResults(int limit, std::vector<std::vector<int>>& queries)
    {
        std::unordered_map<int, int> map1; // map1[i] = num of balls in color i
        std::unordered_map<int, int> map2; // map2[j] = color of ball j
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& query : queries) {
            const auto& ball = query[0];
            const auto& color = query[1];
            if (map2.count(ball)) {
                const auto prevColor = map2[ball];
                if (--map1[prevColor] == 0) {
                    map1.erase(prevColor);
                }
            }
            map1[color]++;
            map2[ball] = color;
            result.push_back(map1.size());
        }
        return result;
    }
};