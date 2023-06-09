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
 */

class Solution
{
public:
    int removeElement(std::vector<int>& nums, int val)
    {
        // two pointers:
        // - keep: store elements that are not equal to "val"
        // - scan: scan all elements
        if (nums.empty())
            return 0;

        int keep = 0;
        for (size_t scan = 0; scan < nums.size(); ++scan) {
            if (nums[scan] != val) {
                nums[keep++] = nums[scan];
            }
        }
        return keep;
    }
};
