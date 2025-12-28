#include <vector>

/**
 * You are given a sorted array consisting of only integers where every element appears exactly
 * twice, except for one element which appears exactly once.
 *
 * Return the single element that appears only once.
 *
 * Your solution must run in O(log n) time and O(1) space.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 */

class Solution {
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // binary search, time O(logN), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums.front();

        // LEFT...MID-2 MID-1 MID MID+1 MID+2...RIGHT
        // |<-----left part---->| |<---right part-->|
        // property1: same elements are adjacent
        // property2: break nums into two parts, the single element is in the part with odd length
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            const int mid = left + (right - left) / 2;
            if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1])
                return nums[mid];

            const bool isLeftPartEvenLength = (mid - left + 1) % 2 == 0;
            if (nums[mid] == nums[mid + 1]) {
                if (isLeftPartEvenLength) {
                    right = mid - 1; // left part skips nums[mid], its length becomes odd
                } else {
                    left = mid + 2;
                }
            } else {
                // nums[mid] == nums[mid - 1]
                if (isLeftPartEvenLength) {
                    left = mid + 1; // right part has odd length
                } else {
                    right = mid - 2;
                }
            }
        }
        return nums[left];
    }

    // bit manipulation, time O(N), space O(1)
    int approach1(const std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return nums.front();

        int result = 0;
        for (const auto& val : nums) {
            result ^= val;
        }
        return result;
    }
};
