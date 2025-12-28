#include <vector>

/**
 * You are given a 0-indexed array of positive integers nums.
 *
 * A subarray of nums is called incremovable if nums becomes strictly increasing on removing the
 * subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because
 * removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly
 * increasing.
 *
 * Return the total number of incremovable subarrays of nums.
 *
 * Note that an empty array is considered strictly increasing.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    int incremovableSubarrayCount(std::vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                std::vector<int> values;
                for (int k = 0; k < i; ++k) {
                    values.push_back(nums[k]);
                }
                for (int k = j + 1; k < n; ++k) {
                    values.push_back(nums[k]);
                }
                if (isStrictlyIncreasing(values)) {
                    result++;
                }
            }
        }
        return result;
    }

private:
    bool isStrictlyIncreasing(const std::vector<int>& values)
    {
        if (values.empty())
            return true;

        for (int i = 0; i + 1 < values.size(); ++i) {
            if (values[i] >= values[i + 1])
                return false;
        }
        return true;
    }
};