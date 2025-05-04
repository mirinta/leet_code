#include <climits>
#include <vector>

/**
 * In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith
 * domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)
 *
 * We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.
 *
 * Return the minimum number of rotations so that all the values in tops are the same, or all the
 * values in bottoms are the same.
 *
 * If it cannot be done, return -1.
 *
 * ! 2 <= tops.length <= 2 * 10^4
 * ! bottoms.length == tops.length
 * ! 1 <= tops[i], bottoms[i] <= 6
 */

class Solution
{
public:
    int minDominoRotations(std::vector<int>& tops, std::vector<int>& bottoms)
    {
        int result = std::min(helper(tops[0], tops, bottoms), helper(tops[0], bottoms, tops));
        result = std::min(result, helper(bottoms[0], tops, bottoms));
        result = std::min(result, helper(bottoms[0], bottoms, tops));
        return result == INT_MAX ? -1 : result;
    }

private:
    int helper(int target, const std::vector<int>& tops, const std::vector<int>& bottoms)
    {
        int rotations = 0;
        for (int i = 0; i < tops.size(); ++i) {
            if (tops[i] != target && bottoms[i] != target)
                return INT_MAX;

            if (tops[i] == target)
                continue;

            rotations += bottoms[i] == target;
        }
        return rotations;
    }
};
