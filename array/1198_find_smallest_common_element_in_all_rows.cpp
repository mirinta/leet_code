#include <unordered_map>
#include <vector>

/**
 * Given an m x n matrix mat where every row is sorted in strictly increasing order, return the
 * smallest common element in all rows.
 *
 * If there is no common element, return -1.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 500
 * ! 1 <= mat[i][j] <= 10^4
 * ! mat[i] is sorted in strictly increasing order.
 */

class Solution {
public:
    int smallestCommonElement(std::vector<std::vector<int>>& mat)
    {
        std::unordered_map<int, int> map; // val to frequency
        for (const auto& row : mat) {
            for (const auto& val : row) {
                map[val]++;
            }
        }
        const int m = mat.size();
        int result = INT_MAX;
        for (const auto& [val, freq] : map) {
            if (freq == m) {
                result = std::min(result, val);
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};