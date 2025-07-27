#include <vector>

/**
 * You are given a 0-indexed integer array nums. An index i is part of a hill in nums if the closest
 * non-equal neighbors of i are smaller than nums[i]. Similarly, an index i is part of a valley in
 * nums if the closest non-equal neighbors of i are larger than nums[i]. Adjacent indices i and j
 * are part of the same hill or valley if nums[i] == nums[j].
 *
 * Note that for an index to be part of a hill or valley, it must have a non-equal neighbor on both
 * the left and right of the index.
 *
 * Return the number of hills and valleys in nums.
 *
 * ! 3 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution
{
public:
    int countHillValley(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> filter;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            filter.push_back(nums[i]);
        }
        int result = 0;
        for (int i = 1; i < filter.size() - 1; ++i) {
            const bool isHill = (filter[i] > filter[i - 1]) && (filter[i] > filter[i + 1]);
            const bool isValley = (filter[i] < filter[i - 1]) && (filter[i] < filter[i + 1]);
            result += isHill || isValley;
        }
        return result;
    }
};