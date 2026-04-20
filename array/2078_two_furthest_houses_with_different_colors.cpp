#include <vector>

/**
 * There are n houses evenly lined up on the street, and each house is beautifully painted. You are given a 0-indexed
 * integer array colors of length n, where colors[i] represents the color of the ith house.
 *
 * Return the maximum distance between two houses with different colors.
 *
 * The distance between the ith and jth houses is abs(i - j), where abs(x) is the absolute value of x.
 *
 * ! n == colors.length
 * ! 2 <= n <= 100
 * ! 0 <= colors[i] <= 100
 * ! Test data are generated such that at least two houses have different colors.
 */

class Solution {
public:
    int maxDistance(std::vector<int>& colors)
    {
        const int n = colors.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = n - 1; j > i; --j) {
                if (colors[j] != colors[i]) {
                    result = std::max(result, j - i);
                    break;
                }
            }
        }
        return result;
    }
};