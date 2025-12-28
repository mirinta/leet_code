#include <vector>

/**
 * 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
 *
 * 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 *
 * 1 <= 数组长度 <= 50000
 *
 * ! 本题与LC 169相同。
 */

class Solution {
public:
    int majorityElement(std::vector<int>& nums)
    {
        int target = 0;
        int votes = 0;
        for (const auto& val : nums) {
            if (votes == 0) {
                target = val;
                votes = 1;
            } else if (val == target) {
                votes++;
            } else {
                votes--;
            }
        }
        return target;
    }

private:
    int approach1(std::vector<int>& nums)
    {
        // find the n/2-th largest element
        // worst case O(n^2)
        int lo = 0;
        int hi = nums.size() - 1;
        const int rank = nums.size() / 2;
        while (lo <= hi) {
            const int pos = partition(lo, hi, nums);
            if (pos == rank)
                return nums[pos];

            if (pos > rank) {
                hi = pos - 1;
            } else {
                lo = pos + 1;
            }
        }
        return -1;
    }

    int partition(int lo, int hi, std::vector<int>& nums)
    {
        const int pivot = nums[lo];
        int i = lo + 1;
        int j = hi;
        while (true) {
            while (i <= hi && nums[i] <= pivot) {
                i++;
            }
            while (j >= 0 && nums[j] > pivot) {
                j--;
            }
            if (i >= j)
                break;

            std::swap(nums[i], nums[j]);
        }
        std::swap(nums[lo], nums[j]);
        return j;
    }
};
