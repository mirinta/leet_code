#include <vector>

/**
 * Given an array of integers called nums, you can perform the following operation while nums
 * contains at least 2 elements:
 *
 * Choose the first two elements of nums and delete them.
 * The score of the operation is the sum of the deleted elements.
 *
 * Your task is to find the maximum number of operations that can be performed, such that all
 * operations have the same score.
 *
 * Return the maximum number of operations possible that satisfy the condition mentioned above.
 *
 * ! 2 <= nums.length <= 100
 * ! 1 <= nums[i] <= 1000
 */

class Solution {
public:
    int maxOperations(std::vector<int>& nums)
    {
        const int n = nums.size();
        int sum = nums[0] + nums[1];
        int result = 1;
        for (int i = 2; i + 1 < n; i += 2) {
            if (nums[i] + nums[i + 1] != sum)
                break;

            result++;
        }
        return result;
    }
};