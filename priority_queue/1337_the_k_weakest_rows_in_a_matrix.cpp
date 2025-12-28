#include <queue>
#include <vector>

/**
 * You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing
 * civilians). The soldiers are positioned in front of the civilians. That is, all the 1's will
 * appear to the left of all the 0's in each row.
 *
 * A row i is weaker than a row j if one of the following is true:
 *
 * - The number of soldiers in row i is less than the number of soldiers in row j.
 *
 * - Both rows have the same number of soldiers and i < j.
 *
 * Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 2 <= n, m <= 100
 * ! 1 <= k <= m
 * ! matrix[i][j] is either 0 or 1.
 */

class Solution {
public:
    std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k)
    {
        const int m = mat.size();
        using Pair = std::pair<int, int>; // num of soldiers, row index
        auto comparator = [](const auto& p1, const auto& p2) {
            return p1.first == p2.first ? p1.second < p2.second : p1.first < p2.first;
        };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator); // max heap
        for (int i = 0; i < m; ++i) {
            auto iter = std::upper_bound(mat[i].rbegin(), mat[i].rend(), 0);
            // soldiers appears to the left of all civilians
            const int soldiers = std::distance(iter, mat[i].rend());
            pq.emplace(soldiers, i);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        std::vector<int> result(std::min<size_t>(pq.size(), k));
        for (int i = result.size() - 1; i >= 0; --i) {
            result[i] = pq.top().second;
            pq.pop();
        }
        return result;
    }
};
