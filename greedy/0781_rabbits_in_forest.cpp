#include <cmath>
#include <unordered_map>
#include <vector>

/**
 * There is a forest with an unknown number of rabbits. We asked n rabbits "How many rabbits have
 * the same color as you?" and collected the answers in an integer array answers where answers[i] is
 * the answer of the ith rabbit.
 *
 * Given the array answers, return the minimum number of rabbits that could be in the forest.
 *
 * ! 1 <= answers.length <= 1000
 * ! 0 <= answers[i] < 1000
 */

class Solution
{
public:
    int numRabbits(std::vector<int>& answers)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : answers) {
            map[val]++;
        }
        int result = 0;
        for (const auto& [val, count] : map) {
            // each group contains at most (val+1) rabbits
            result += std::ceil(1.0 * count / (val + 1)) * (val + 1);
        }
        return result;
    }
};
