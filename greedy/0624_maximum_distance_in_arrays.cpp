#include <vector>

/**
 * You are given m arrays, where each array is sorted in ascending order.
 *
 * You can pick up two integers from two different arrays (each array picks one) and calculate the
 * distance.
 *
 * We define the distance between two integers a and b to be their absolute difference |a - b|.
 *
 * Return the maximum distance.
 *
 * ! m == arrays.length
 * ! 2 <= m <= 10^5
 * ! 1 <= arrays[i].length <= 500
 * ! -10^4 <= arrays[i][j] <= 10^4
 * ! arrays[i] is sorted in ascending order.
 * ! There will be at most 10^5 integers in all the arrays.
 */

class Solution {
public:
    int maxDistance(std::vector<std::vector<int>>& arrays)
    {
        const int n = arrays.size();
        int min = arrays[0].front();
        int max = arrays[0].back();
        int result = 0;
        for (int i = 1; i < n; ++i) {
            result = std::max({result, std::abs(max - arrays[i].front()), std::abs(arrays[i].back() - min)});
            min = std::min(min, arrays[i].front());
            max = std::max(max, arrays[i].back());
        }
        return result;
    }
};