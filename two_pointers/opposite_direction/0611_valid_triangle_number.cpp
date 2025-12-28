#include <algorithm>
#include <vector>

/**
 * Given an integer array nums, return the number of triplets chosen from the array that can make
 * triangles if we take them as side lengths of a triangle.
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 1000
 */

class Solution {
public:
    int triangleNumber(std::vector<int>& nums)
    {
        if (nums.size() < 3)
            return 0;

        // a valid triangle requires nums[i] + nums[j] > nums[k]
        // nums[i], nums[j] and nums[k] is positive
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = 0;
        for (int k = n - 1; k >= 2; --k) {
            int i = 0;
            int j = k - 1;
            while (i < j) {
                if (nums[i] + nums[j] > nums[k]) {
                    result += j - i; // (i,j,k),(i+1,j,k),...,(j-1,j,k) are valid triangles
                    j--;
                } else {
                    i++;
                }
            }
        }
        return result;
    }
};