#include <vector>

/**
 * 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
 *
 * 给你一个可能存在 重复 元素值的数组 numbers ，它原来是一个升序排列的数组，并按上述情形进行了一次旋转。请返回旋转数组的最小元素。例如，数组 [3,4,5,1,2]
 * 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为 1。  
 *
 * 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ...,
 * a[n-2]] 。
 *
 * ! n == numbers.length
 * ! 1 <= n <= 5000
 * ! -5000 <= numbers[i] <= 5000
 * ! numbers 原来是一个升序排序的数组，并进行了 1 至 n 次旋转
 *
 * ! 本题与LC 154相同。
 */

class Solution {
public:
    int minArray(const std::vector<int>& nums)
    {
        const auto n = nums.size();
        if (n <= 1)
            return n == 1 ? nums[0] : 0;

        // NOTE: the array may contain duplicates
        // no way to early return
        // | 1 1 | 0 1 |
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                // nums[left:mid] are in the right part, skip them
                left = mid + 1;
            } else if (nums[mid] < nums[right]) {
                // nums[mid] is in the left part, shrink its size
                right = mid;
            } else {
                // nums[mid] == nums[right],
                // no way to determine which part contains nums[mid],
                // we can simply skip nums[right]
                right -= 1;
            }
        }
        return nums[left];
    }
};