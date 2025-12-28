#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums. In one operation, you can replace any element in nums with
 * any integer.
 *
 * nums is considered continuous if both of the following conditions are fulfilled:
 *
 * - All elements in nums are unique.
 *
 * - The difference between the maximum element and the minimum element in nums equals
 * nums.length 1.
 *
 * For example, nums = [4, 2, 5, 3] is continuous, but nums = [1, 2, 3, 5, 6] is not continuous.
 *
 * Return the minimum number of operations to make nums continuous.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums)
    {
        // let x be the min of modified nums
        // then elements in nums must be {x,x+1,x+2,...,x+n-1}
        // enumerate x = nums[i] as the min element of the modified nums
        // let count(x) = num of elements which are already in the range [x:x+n-1]
        // then #operations = n - count(x)
        const int n = nums.size();
        std::unordered_set<int> set(nums.begin(), nums.end());
        std::vector<int> uniques(set.begin(), set.end());
        std::sort(uniques.begin(), uniques.end());
        int result = INT_MAX;
        for (int i = 0, j = 0; i < uniques.size(); ++i) {
            while (j < uniques.size() && uniques[j] - uniques[i] <= n - 1) {
                j++;
            }
            result = std::min(result, n - (j - i));
        }
        return result;
    }
};
