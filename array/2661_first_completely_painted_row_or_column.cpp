#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both
 * contain all the integers in the range [1, m * n].
 *
 * Go through each index i in arr starting from index 0 and paint the cell in mat containing the
 * integer arr[i].
 *
 * Return the smallest index i at which either a row or a column will be completely painted in mat.
 *
 * ! m == mat.length
 * ! n = mat[i].length
 * ! arr.length == m * n
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 10^5
 * ! 1 <= arr[i], mat[r][c] <= m * n
 * ! All the integers of arr are unique.
 * ! All the integers of mat are unique.
 */

class Solution {
public:
    int firstCompleteIndex(std::vector<int>& arr, std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        std::unordered_map<int, std::pair<int, int>> map;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                map[mat[i][j]] = {i, j};
            }
        }
        std::vector<int> countRow(m, 0);
        std::vector<int> countCol(n, 0);
        for (int i = 0; i < arr.size(); ++i) {
            const auto& [x, y] = map[arr[i]];
            countRow[x]++;
            countCol[y]++;
            if (countRow[x] == n || countCol[y] == m)
                return i;
        }
        return -1;
    }
};
