#include <algorithm>
#include <vector>

/**
 * A permutation of an array of integers is an arrangement of its members into a sequence or linear
 * order.
 *
 * - For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3],
 * [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
 *
 * The next permutation of an array of integers is the next lexicographically greater permutation of
 * its integer. More formally, if all the permutations of the array are sorted in one container
 * according to their lexicographical order, then the next permutation of that array is the
 * permutation that follows it in the sorted container. If such arrangement is not possible, the
 * array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
 *
 * - For example, the next permutation of arr = [1,2,3] is [1,3,2].
 *
 * - Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
 *
 * - While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a
 * lexicographical larger rearrangement.
 *
 * Given an array of integers nums, find the next permutation of nums.
 *
 * The replacement must be in place and use only constant extra memory.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 100
 */

class Solution {
public:
    void nextPermutation(std::vector<int>& nums)
    {
        if (nums.size() == 1)
            return;

        const int n = nums.size();
        int i = n - 1;
        while (i >= 1 && nums[i] <= nums[i - 1]) {
            i--;
        }
        // case 1: nums is the largest permutation
        if (i == 0) {
            std::reverse(nums.begin(), nums.end());
            return;
        }
        // case 2: nums is the smallest permutation
        if (i == n - 1) {
            std::swap(nums[n - 1], nums[n - 2]);
            return;
        }
        // case 3: X X X i-1 i X X j X X n-1
        //                   |<-decreasing->|
        // find the largest j such that nums[j] > nums[i-1]
        // swap nums[j] and nums[i-1]
        // and sort nums[i:n-1] in non-decreasing order
        int j = n - 1;
        while (j > i && nums[j] <= nums[i - 1]) {
            j--;
        }
        std::swap(nums[j], nums[i - 1]);
        std::reverse(nums.begin() + i, nums.end());
    }
};