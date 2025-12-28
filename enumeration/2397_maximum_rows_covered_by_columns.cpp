#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * You are given a 0-indexed m x n binary matrix matrix and an integer numSelect, which denotes the
 * number of distinct columns you must select from matrix.
 *
 * Let us consider s = {c_1, c_2, ...., c_numSelect} as the set of columns selected by you. A row
 * row is covered by s if:
 *
 * - For each cell matrix[row][col] (0 <= col <= n - 1) where matrix[row][col] == 1, col is present
 * in s or,
 *
 * - No cell in row has a value of 1. You need to choose numSelect columns such that the number
 * of rows that are covered is maximized.
 *
 * Return the maximum number of rows that can be covered by a set of numSelect columns.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 12
 * ! matrix[i][j] is either 0 or 1.
 * ! 1 <= numSelect <= n
 */

class Solution {
public:
    int maximumRows(const std::vector<std::vector<int>>& matrix, int numSelect)
    {
        return approach2(matrix, numSelect);
    }

private:
    // enumeration with bitmask
    int approach2(const std::vector<std::vector<int>>& matrix, int numSelect)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        // encode each row into a binary number
        std::vector<int> rows(m);
        for (int i = 0; i < m; ++i) {
            int num = 0;
            for (int j = 0; j < n; ++j) {
                num = num * 2 + matrix[i][j];
            }
            rows[i] = num;
        }
        auto binaryOnes = [](int num) {
            int count = 0;
            while (num) {
                count++;
                num &= num - 1;
            }
            return count;
        };
        int result = 0;
        for (int state = 0; state < (1 << n); ++state) {
            if (binaryOnes(state) != numSelect)
                continue;

            const int count =
                std::count_if(rows.begin(), rows.end(), [&state](const auto& val) { return (state & val) == val; });
            result = std::max(result, count);
        }
        return result;
    }

    int approach1(const std::vector<std::vector<int>>& matrix, int numSelect)
    {
        int result = 0;
        std::unordered_set<int> selected;
        backtrack(result, selected, 0, numSelect, matrix);
        return result;
    }

    void backtrack(int& result,
                   std::unordered_set<int>& selected,
                   int start,
                   int numSelect,
                   const std::vector<std::vector<int>>& matrix)
    {
        if (selected.size() == numSelect) {
            int count = 0;
            for (const auto& row : matrix) {
                int totalSum = 0;
                int selectedSum = 0;
                for (int col = 0; col < row.size(); ++col) {
                    totalSum += row[col];
                    if (selected.count(col)) {
                        selectedSum += row[col];
                    }
                }
                if (totalSum == selectedSum) {
                    count++;
                }
            }
            result = std::max(result, count);
            return;
        }
        for (int j = start; j < matrix[0].size(); ++j) {
            selected.insert(j);
            backtrack(result, selected, j + 1, numSelect, matrix);
            selected.erase(j);
        }
    }
};