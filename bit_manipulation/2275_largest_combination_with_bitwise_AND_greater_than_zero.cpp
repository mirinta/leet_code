#include <array>
#include <vector>

/**
 * The bitwise AND of an array nums is the bitwise AND of all integers in nums.
 *
 * - For example, for nums = [1, 5, 3], the bitwise AND is equal to 1 & 5 & 3 = 1.
 *
 * - Also, for nums = [7], the bitwise AND is 7.
 *
 * You are given an array of positive integers candidates. Evaluate the bitwise AND of every
 * combination of numbers of candidates. Each number in candidates may only be used once in each
 * combination.
 *
 * Return the size of the largest combination of candidates with a bitwise AND greater than 0.
 *
 * ! 1 <= candidates.length <= 10^5
 * ! 1 <= candidates[i] <= 10^7
 */

class Solution {
public:
    int largestCombination(std::vector<int>& candidates)
    {
        std::array<int, 24> count{};
        int result = 0;
        for (const auto& val : candidates) {
            for (int i = 0; i < 24; ++i) {
                if ((val >> i) & 1) {
                    count[i]++;
                    result = std::max(result, count[i]);
                }
            }
        }
        return result;
    }
};