#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums. You need to ensure that the elements in the array are
 * distinct. To achieve this, you can perform the following operation any number of times:
 *
 * - Remove 3 elements from the beginning of the array. If the array has fewer than 3 elements,
 * remove all remaining elements.
 *
 * Note that an empty array is considered to have distinct elements. Return the minimum number of
 * operations needed to make the elements in the array distinct.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution
{
public:
    int minimumOperations(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_set<int> set;
        for (int i = n - 1; i >= 0; --i) {
            if (!set.insert(nums[i]).second)
                return i / 3 + 1;
        }
        return 0;
    }
};
