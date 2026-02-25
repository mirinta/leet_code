#include <vector>

/**
 * You are given an integer array nums, where nums[i] represents the points scored in the ith game.
 *
 * There are exactly two players. Initially, the first player is active and the second player is inactive.
 *
 * The following rules apply sequentially for each game i:
 *
 * - If nums[i] is odd, the active and inactive players swap roles.
 *
 * - In every 6th game (that is, game indices 5, 11, 17, ...), the active and inactive players swap roles.
 *
 * - The active player plays the ith game and gains nums[i] points.
 *
 * Return the score difference, defined as the first player's total score minus the second players's total score
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 */

class Solution {
public:
    int scoreDifference(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 0, flag = 1; i < n; ++i) {
            flag *= i % 6 == 5 ? -1 : 1;
            flag *= nums[i] % 2 ? -1 : 1;
            result += flag * nums[i];
        }
        return result;
    }
};