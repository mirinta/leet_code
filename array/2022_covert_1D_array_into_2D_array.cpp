#include <vector>

/**
 * You are given a 0-indexed 1-dimensional (1D) integer array original, and two integers, m and n.
 * You are tasked with creating a 2-dimensional (2D) array with  m rows and n columns using all the
 * elements from original.
 *
 * The elements from indices 0 to n - 1 (inclusive) of original should form the first row of the
 * constructed 2D array, the elements from indices n to 2 * n - 1 (inclusive) should form the second
 * row of the constructed 2D array, and so on.
 *
 * Return an m x n 2D array constructed according to the above procedure, or an empty 2D array if it
 * is impossible.
 *
 * ! 1 <= original.length <= 5 * 10^4
 * ! 1 <= original[i] <= 10^5
 * ! 1 <= m, n <= 4 * 10^4
 */

class Solution {
public:
    std::vector<std::vector<int>> construct2DArray(std::vector<int>& original, int m, int n)
    {
        if (m * n != original.size())
            return {};

        std::vector<std::vector<int>> result(m, std::vector<int>(n));
        for (int k = 0; k < original.size(); ++k) {
            result[k / n][k % n] = original[k];
        }
        return result;
    }
};