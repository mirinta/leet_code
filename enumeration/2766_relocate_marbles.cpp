#include <set>
#include <vector>

/**
 * You are given a 0-indexed integer array nums representing the initial positions of some marbles.
 * You are also given two 0-indexed integer arrays moveFrom and moveTo of equal length.
 *
 * Throughout moveFrom.length steps, you will change the positions of the marbles. On the ith step,
 * you will move all marbles at position moveFrom[i] to position moveTo[i].
 *
 * After completing all the steps, return the sorted list of occupied positions.
 *
 * Notes:
 *
 * - We call a position occupied if there is at least one marble in that position.
 *
 * - There may be multiple marbles in a single position.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= moveFrom.length <= 10^5
 * ! moveFrom.length == moveTo.length
 * ! 1 <= nums[i], moveFrom[i], moveTo[i] <= 10^9
 * ! The test cases are generated such that there is at least a marble in moveFrom[i] at the moment
 * ! we want to apply the ith move.
 */

class Solution {
public:
    std::vector<int> relocateMarbles(std::vector<int>& nums, std::vector<int>& moveFrom, std::vector<int>& moveTo)
    {
        std::set<int> set(nums.begin(), nums.end());
        for (int i = 0; i < moveFrom.size(); ++i) {
            set.erase(moveFrom[i]);
            set.insert(moveTo[i]);
        }
        return {set.begin(), set.end()};
    }
};