#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given two arrays, instructions and values, both of size n.
 *
 * You need to simulate a process based on the following rules:
 *
 * - You start at the first instruction at index i = 0 with an initial score of 0.
 *
 * - If instructions[i] is "add":
 *
 *   - Add values[i] to your score.
 *
 *   - Move to the next instruction (i + 1).
 *
 * - If instructions[i] is "jump":
 *
 *   - Move to the instruction at index (i + values[i]) without modifying your score.
 *
 * The process ends when you either:
 *
 * - Go out of bounds (i.e., i < 0 or i >= n), or
 *
 * - Attempt to revisit an instruction that has been previously executed. The revisited instruction
 * is not executed.
 *
 * Return your score at the end of the process.
 *
 * ! n == instructions.length == values.length
 * ! 1 <= n <= 10^5
 * ! instructions[i] is either "add" or "jump".
 * ! -10^5 <= values[i] <= 10^5
 */

class Solution
{
public:
    long long calculateScore(std::vector<std::string>& instructions, std::vector<int>& values)
    {
        const int n = instructions.size();
        std::unordered_set<int> visited;
        long long result = 0;
        int i = 0;
        while (i >= 0 && i < n && visited.insert(i).second) {
            if (instructions[i] == "add") {
                result += values[i];
                i++;
            } else {
                i += values[i];
            }
        }
        return result;
    }
};
