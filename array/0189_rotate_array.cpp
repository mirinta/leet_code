#include <vector>

/**
 * Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -2^31 <= nums[i] <= 2^31 - 1
 * ! 0 <= k <= 10^5
 */

class Solution {
public:
    void rotate(std::vector<int>& nums, int k)
    {
        approach2(nums, k);
    }

private:
    // time O(N), space O(1)
    void approach2(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        k = k % n;
        if (k == 0)
            return;

        // reverse all elements: 1 2 3 [4 5 6] => [6 5 4] 3 2 1
        std::reverse(nums.begin(), nums.end());
        // reverse first k elements: [6 5 4] 3 2 1 => [4 5 6] 3 2 1
        std::reverse(nums.begin(), nums.begin() + k);
        // reverse last n-k elements: [4 5 6] 3 2 1 => [4 5 6] 1 2 3
        std::reverse(nums.begin() + k, nums.end());
    }

    // time O(N), space O(N)
    void approach1(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        k = k % n;
        if (k == 0)
            return;

        std::vector<int> backup(nums);
        for (int i = 0; i < k; ++i) {
            nums[i] = backup[n - k + i];
        }
        for (int i = k; i < n; ++i) {
            nums[i] = backup[i - k];
        }
    }
};