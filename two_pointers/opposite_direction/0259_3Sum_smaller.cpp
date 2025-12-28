#include <algorithm>
#include <vector>

/**
 * Given an array of n integers nums and an integer target, find the number of index triplets i, j,
 * k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
 *
 * ! n == nums.length
 * ! 0 <= n <= 3500
 * ! -100 <= nums[i] <= 100
 * ! -100 <= target <= 100
 */

class Solution {
public:
    int threeSumSmaller(std::vector<int>& nums, int target)
    {
        if (nums.size() < 3)
            return 0;

        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = 0;
        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] + nums[i + 1] + nums[i + 2] >= target)
                break;

            int j = i + 1;
            int k = n - 1;
            while (j < k) {
                if (nums[i] + nums[j] + nums[k] < target) {
                    result += k - j; // (i,j,k),(i,j,k-1),...,(i,j,j+1) are valid triplets
                    j++;
                } else {
                    k--;
                }
            }
        }
        return result;
    }
};