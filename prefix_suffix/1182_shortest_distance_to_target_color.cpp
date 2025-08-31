#include <array>
#include <climits>
#include <vector>

/**
 * You are given an array colors, in which there are three colors: 1, 2 and 3.
 *
 * You are also given some queries. Each query consists of two integers i and c, return the shortest
 * distance between the given index i and the target color c. If there is no solution return -1.
 *
 * ! 1 <= colors.length <= 5*10^4
 * ! 1 <= colors[i] <= 3
 * ! 1 <= queries.length <= 5*10^4
 * ! queries[i].length == 2
 * ! 0 <= queries[i][0] < colors.length
 * ! 1 <= queries[i][1] <= 3
 */

class Solution
{
public:
    std::vector<int> shortestDistanceColor(std::vector<int>& colors,
                                           std::vector<std::vector<int>>& queries)
    {
        const int n = colors.size();
        std::vector<std::array<int, 4>> prefix(n, {-1, -1, -1, -1});
        std::vector<std::array<int, 4>> suffix(n, {-1, -1, -1, -1});
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                prefix[i] = prefix[i - 1];
            }
            prefix[i][colors[i]] = i;
        }
        for (int i = n - 1; i >= 0; --i) {
            if (i < n - 1) {
                suffix[i] = suffix[i + 1];
            }
            suffix[i][colors[i]] = i;
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            const auto& i = q[0];
            const auto& c = q[1];
            const int d1 = prefix[i][c] == -1 ? INT_MAX : i - prefix[i][c];
            const int d2 = suffix[i][c] == -1 ? INT_MAX : suffix[i][c] - i;
            const int min = std::min(d1, d2);
            result.emplace_back(min == INT_MAX ? -1 : min);
        }
        return result;
    }
};
