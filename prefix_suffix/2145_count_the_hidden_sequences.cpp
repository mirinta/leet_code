#include <vector>

/**
 * You are given a 0-indexed array of n integers differences, which describes the differences
 * between each pair of consecutive integers of a hidden sequence of length (n + 1). More formally,
 * call the hidden sequence hidden, then we have that differences[i] = hidden[i + 1] - hidden[i].
 *
 * You are further given two integers lower and upper that describe the inclusive range of values
 * [lower, upper] that the hidden sequence can contain.
 *
 * - For example, given differences = [1, -3, 4], lower = 1, upper = 6, the hidden sequence is a
 * sequence of length 4 whose elements are in between 1 and 6 (inclusive).
 *
 *   - [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences.
 *
 *   - [5, 6, 3, 7] is not possible since it contains an element greater than 6.
 *
 *   - [1, 2, 3, 4] is not possible since the differences are not correct.
 *
 * Return the number of possible hidden sequences there are. If there are no possible sequences,
 * return 0.
 *
 * ! n == differences.length
 * ! 1 <= n <= 10^5
 * ! -10^5 <= differences[i] <= 10^5
 * ! -10^5 <= lower <= upper <= 10^5
 */

class Solution {
public:
    int numberOfArrays(std::vector<int>& differences, int lower, int upper)
    {
        // let hidden[0] = x
        // hidden[1] = x + diff[0]
        // hidden[2] = x + sum of diff[0:1]
        // ...
        // hidden[n] = x + sum of diff[::]
        int diff = 0;
        int min = 0;
        int max = 0;
        for (const auto& d : differences) {
            diff += d;
            min = std::min(min, diff);
            max = std::max(max, diff);
            if (max - min > upper - lower)
                return 0;
        }
        return (upper - lower) - (max - min) + 1;
    }
};
