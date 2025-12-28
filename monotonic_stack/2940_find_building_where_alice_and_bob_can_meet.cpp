#include <stack>
#include <vector>

/**
 * You are given a 0-indexed array heights of positive integers, where heights[i] represents the
 * height of the ith building.
 *
 * If a person is in building i, they can move to any other building j if and only if i < j and
 * heights[i] < heights[j].
 *
 * You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is
 * in building ai while Bob is in building bi.
 *
 * Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can
 * meet on the ith query. If Alice and Bob cannot move to a common building on query i, set ans[i]
 * to -1.
 *
 * ! 1 <= heights.length <= 5 * 10^4
 * ! 1 <= heights[i] <= 10^9
 * ! 1 <= queries.length <= 5 * 10^4
 * ! queries[i] = [ai, bi]
 * ! 0 <= ai, bi <= heights.length - 1
 */

class Solution {
public:
    std::vector<int> leftmostBuildingQueries(std::vector<int>& heights, std::vector<std::vector<int>>& queries)
    {
        std::vector<std::vector<std::pair<int, int>>> newQueries(heights.size());
        std::vector<int> result(queries.size());
        result.reserve(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int a = queries[i][0];
            int b = queries[i][1];
            if (a > b) {
                std::swap(a, b);
            }
            if (a == b || heights[a] < heights[b]) {
                result[i] = b;
            } else {
                newQueries[b].emplace_back(a, i);
            }
        }
        std::vector<int> vec; // heights of vec[0:k] is monotonic decreasing
        for (int i = heights.size() - 1; i >= 0; --i) {
            for (const auto& [a, q] : newQueries[i]) {
                result[q] = binarySearch(a, heights, vec);
            }
            while (!vec.empty() && heights[vec.back()] <= heights[i]) {
                vec.pop_back();
            }
            vec.push_back(i);
        }
        return result;
    }

private:
    int binarySearch(int a, const std::vector<int>& heights, const std::vector<int>& vec)
    {
        int lo = 0;
        int hi = vec.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (heights[vec[mid]] > heights[a]) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return hi == -1 ? -1 : vec[hi];
    }
};