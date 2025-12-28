#include <vector>

/**
 * Given an integer array nums which is sorted in ascending order and all of its elements are unique
 * and given also an integer k, return the kth missing number starting from the leftmost number of
 * the array.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 1 <= nums[i] <= 10^7
 * ! nums is sorted in ascending order, and all the elements are unique.
 * ! 1 <= k <= 10^8
 */

class Solution {
public:
    int missingElement(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // time O(logN), space O(1)
    int approach2(const std::vector<int>& nums, int k)
    {
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int missing = nums[mid] - nums.front() - mid;
            if (missing < k) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return nums[hi] + k - (nums[hi] - nums.front() - hi);
    }

    // time O(N), space O(1)
    int approach1(const std::vector<int>& nums, int k)
    {
        // index: 0 1 2 3
        // value: 4 7 9 10
        // 4~7, missing two numbers, {5,6}
        // 7~9, missing one number, {1}
        // 9~10, no missing number. {}
        const int n = nums.size();
        int count = 0;
        for (int i = 0; i < n - 1; ++i) {
            const int missing = nums[i + 1] - nums[i] - 1;
            if (missing >= k)
                return nums[i] + k;

            k -= missing;
        }
        return nums.back() + k;
    }
};