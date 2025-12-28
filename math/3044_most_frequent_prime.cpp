#include <unordered_map>
#include <vector>

/**
 * You are given a m x n 0-indexed 2D matrix mat. From every cell, you can create numbers in the
 * following way:
 *
 * - There could be at most 8 paths from the cells namely: east, south-east, south, south-west,
 * west, north-west, north, and north-east.
 *
 * - Select a path from them and append digits in this path to the number being formed by traveling
 * in this direction.
 *
 * - Note that numbers are generated at every step, for example, if the digits along the path are 1,
 * 9, 1, then there will be three numbers generated along the way: 1, 19, 191.
 *
 * Return the most frequent prime number greater than 10 out of all the numbers created by
 * traversing the matrix or -1 if no such prime number exists. If there are multiple prime numbers
 * with the highest frequency, then return the largest among them.
 *
 * Note: It is invalid to change the direction during the move.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 6
 * ! 1 <= mat[i][j] <= 9
 */

class Solution {
public:
    int mostFrequentPrime(std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (const auto& [dx, dy] : kDirections) {
                    helper(i, j, dx, dy, mat);
                }
            }
        }
        int result = -1;
        int maxFreq = 0;
        for (const auto& [num, freq] : map) {
            if (freq > maxFreq) {
                result = num;
                maxFreq = freq;
            } else if (freq == maxFreq) {
                result = std::max(result, num);
            }
        }
        return result;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0},  {-1, 0},
                                                       {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    std::unordered_map<int, int> map;

    void helper(int i, int j, int dx, int dy, const std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        int num = 0;
        for (int x = i, y = j; x >= 0 && x < m && y >= 0 && y < n; x += dx, y += dy) {
            num = num * 10 + mat[x][y];
            if (num > 10 && isPrime(num)) {
                map[num]++;
            }
        }
    }

    bool isPrime(int n)
    {
        if (n < 2)
            return false;

        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0)
                return false;
        }
        return true;
    }
};