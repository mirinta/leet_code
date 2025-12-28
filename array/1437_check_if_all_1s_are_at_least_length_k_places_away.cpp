#include <vector>

/**
 * Given an binary array nums and an integer k, return true if all 1's are at least k places away
 * from each other, otherwise return false.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= k <= nums.length
 * ! nums[i] is 0 or 1
 */

class Solution {
public:
    bool kLengthApart(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        for (int i = 0, last = -1; i < n; ++i) {
            if (nums[i] == 0)
                continue;

            if (last != -1 && i - last - 1 < k)
                return false;

            last = i;
        }
        return true;
    }
};
