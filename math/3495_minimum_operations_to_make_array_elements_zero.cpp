#include <vector>

/**
 * You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines
 * an array of integers nums consisting of elements ranging from l to r, both inclusive.
 *
 * In one operation, you can:
 *
 * - Select two integers a and b from the array.
 *
 * - Replace them with floor(a / 4) and floor(b / 4).
 *
 * Your task is to determine the minimum number of operations required to reduce all elements of the
 * array to zero for each query. Return the sum of the results for all queries.
 *
 * ! 1 <= queries.length <= 105
 * ! queries[i].length == 2
 * ! queries[i] == [l, r]
 * ! 1 <= l < r <= 109
 */

class Solution {
public:
    long long minOperations(std::vector<std::vector<int>>& queries)
    {
        long long result = 0;
        for (const auto& q : queries) {
            result += (helper(q[1]) - helper(q[0] - 1) + 1) / 2;
        }
        return result;
    }

private:
    // total num of operations to make each individual element of [1, 2, ..., max] zero
    long long helper(long long max)
    {
        // {1, 2, 3}, length of binary representation = 1 and 2, #operations = 1 = ceil(L/2)
        // {4, 5, ..., 15}, length of binary representation = 3 and 4, #operations = 2 = ceil(L/2)
        long long powerOf2 = 1;
        long long L = 1;
        long long result = 0;
        while (powerOf2 <= max) {
            result += (L + 1) / 2 * (std::min(powerOf2 * 2 - 1, max) - powerOf2 + 1);
            powerOf2 *= 2;
            L++;
        }
        return result;
    }
};