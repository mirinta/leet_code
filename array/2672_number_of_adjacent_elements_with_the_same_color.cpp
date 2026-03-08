#include <vector>

/**
 * You are given an integer n representing an array colors of length n where all elements are set to 0's meaning
 * uncolored. You are also given a 2D integer array queries where queries[i] = [indexi, colori]. For the ith query:
 *
 * - Set colors[indexi] to colori.
 *
 * - Count the number of adjacent pairs in colors which have the same color (regardless of colori).
 *
 * Return an array answer of the same length as queries where answer[i] is the answer to the ith query.
 *
 * ! 1 <= n <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 2
 * ! 0 <= indexi <= n - 1
 * ! 1 <=  colori <= 10^5
 */

class Solution {
public:
    std::vector<int> colorTheArray(int n, std::vector<std::vector<int>>& queries)
    {
        std::vector<int> colors(n, 0);
        int count = 0;
        std::vector<int> result;
        result.reserve(n);
        for (const auto& q : queries) {
            const auto& index = q[0];
            const auto& color = q[1];
            if (colors[index] != color) {
                count -= index > 0 && colors[index - 1] != 0 && colors[index - 1] == colors[index];
                count -= index + 1 < n && colors[index + 1] != 0 && colors[index + 1] == colors[index];
                count += index > 0 && colors[index - 1] == color;
                count += index + 1 < n && colors[index + 1] == color;
                colors[index] = color;
            }
            result.push_back(count);
        }
        return result;
    }
};