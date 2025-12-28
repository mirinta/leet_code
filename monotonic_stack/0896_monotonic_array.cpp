#include <vector>

/**
 * An array is monotonic if it is either monotone increasing or monotone decreasing.
 *
 * An array "nums" is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array "nums" is
 * monotone decreasing if for all i <= j, nums[i] >= nums[j].
 *
 * Given an integer array "nums", return true if the given array is monotonic, or false otherwise.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^5 <= nums[i] <= 10^5
 */

class Solution {
public:
    bool isMonotonic(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // one-pass, time O(N), space O(1)
    bool approach2(const std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return true;

        bool isIncreasing = true;
        bool isDecreasing = true;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < nums[i - 1]) {
                isIncreasing = false;
            } else if (nums[i] > nums[i - 1]) {
                isDecreasing = false;
            }
        }
        return isIncreasing || isDecreasing;
    }

    // two-pass, time O(N), space O(1)
    bool approach1(const std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return true;

        auto isIncreasing = [](const std::vector<int>& nums) {
            for (int i = 1; i < nums.size(); ++i) {
                if (nums[i] < nums[i - 1])
                    return false;
            }
            return true;
        };
        auto isDecreasing = [](const std::vector<int>& nums) {
            for (int i = 1; i < nums.size(); ++i) {
                if (nums[i] > nums[i - 1])
                    return false;
            }
            return true;
        };
        return isIncreasing(nums) || isDecreasing(nums);
    }
};