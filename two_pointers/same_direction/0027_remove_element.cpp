#include <vector>

/**
 * Given an integer array "nums" and an integer "val", remove all occurrences of "val" in "nums"
 * in-place. The order of the elements may be changed. Then return the number of elements in "nums"
 * which are not equal to "val".
 *
 * Consider the number of elements in "nums" which are not equal to "val" be "k", to get accepted,
 * you need to do the following things:
 *
 * - Change the array "nums" such that the first "k" elements of "nums" contain the elements which
 * are not equal to "val". The remaining elements of nums are not important as well as the size of
 * nums.
 *
 * - Return "k".
 *
 * ! 0 <= nums.length <= 100
 * ! 0 <= nums[i] <= 50
 * ! 0 <= val <= 100
 */

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val)
    {
        const int n = nums.size();
        int i = 0;
        for (int j = 0; j < n; ++j) {
            if (nums[j] != val) {
                std::swap(nums[i], nums[j]);
                i++;
            }
        }
        return i;
    }
};
