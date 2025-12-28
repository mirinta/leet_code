#include <climits>
#include <vector>

/**
 * Given an array nums, you can perform the following operation any number of times:
 *
 * - Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the
 * leftmost one.
 *
 * - Replace the pair with their sum. Return the minimum number of operations needed to make the
 * array non-decreasing.
 *
 * An array is said to be non-decreasing if each element is greater than or equal to its previous
 * element (if it exists).
 *
 * ! 1 <= nums.length <= 50
 * ! -1000 <= nums[i] <= 1000
 */

class Solution {
public:
    int minimumPairRemoval(std::vector<int>& nums)
    {
        int result = 0;
        while (!isValid(nums)) {
            apply(nums);
            result++;
        }
        return result;
    }

private:
    bool isValid(const std::vector<int>& nums)
    {
        for (int i = 0; i + 1 < nums.size(); ++i) {
            if (nums[i + 1] < nums[i])
                return false;
        }
        return true;
    }

    void apply(std::vector<int>& nums)
    {
        int minSum = INT_MAX;
        int minIdx = -1;
        for (int i = 0; i + 1 < nums.size(); ++i) {
            const int sum = nums[i] + nums[i + 1];
            if (sum < minSum) {
                minSum = sum;
                minIdx = i;
            }
        }
        nums[minIdx] = minSum;
        nums.erase(nums.begin() + minIdx + 1);
    }
};
