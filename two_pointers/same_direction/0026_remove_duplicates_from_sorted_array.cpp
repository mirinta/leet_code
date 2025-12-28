#include <vector>

/**
 * Given an integer array "nums" sorted in non-decreasing order, remove the duplicates in-place such
 * that each unique element appears only once. The relative order of the elements should be kept the
 * same. Then return the number of unique elements in "nums".
 *
 * Consider the number of unique elements of "nums" to be "k", to get accepted, you need to do the
 * following steps:
 *
 * - Change the array "nums" such that the first "k" elements of "nums" contain the unique elements
 * in the order they were present in "nums" initially. The remaining elements of "nums" are not
 * important as well as the size of "nums".
 *
 * - Return "k".
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -100 <= nums[i] <= 100
 * ! nums is sorted in non-decreasing order.
 */

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        const int n = nums.size();
        int keep = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] != nums[keep]) {
                nums[++keep] = nums[i];
            }
        }
        return keep + 1;
    }
};