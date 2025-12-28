#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of even length and there is also an empty array arr.
 * Alice and Bob decided to play a game where in every round Alice and Bob will do one move. The
 * rules of the game are as follows:
 *
 * - Every round, first Alice will remove the minimum element from nums, and then Bob does the same.
 *
 * - Now, first Bob will append the removed element in the array arr, and then Alice does the same.
 *
 * - The game continues until nums becomes empty.
 *
 * Return the resulting array arr.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 * ! nums.length % 2 == 0
 */

class Solution {
public:
    std::vector<int> numberGame(std::vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        std::vector<int> result;
        for (int i = 0; i + 1 < nums.size(); i += 2) {
            result.push_back(nums[i + 1]);
            result.push_back(nums[i]);
        }
        return result;
    }
};