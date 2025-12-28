#include <vector>

/**
 * You are given a 1-indexed array of distinct integers nums of length n.
 *
 * You need to distribute all the elements of nums between two arrays arr1 and arr2 using n
 * operations. In the first operation, append nums[1] to arr1. In the second operation, append
 * nums[2] to arr2. Afterwards, in the ith operation:
 *
 * - If the last element of arr1 is greater than the last element of arr2, append nums[i] to arr1.
 * Otherwise, append nums[i] to arr2.
 *
 * The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 ==
 * [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].
 *
 * Return the array result.
 *
 * ! 3 <= n <= 50
 * ! 1 <= nums[i] <= 100
 * ! All elements in nums are distinct.
 */

class Solution {
public:
    std::vector<int> resultArray(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> v1{nums[0]};
        std::vector<int> v2{nums[1]};
        for (int i = 2; i < n; ++i) {
            if (v1.back() > v2.back()) {
                v1.push_back(nums[i]);
            } else {
                v2.push_back(nums[i]);
            }
        }
        v1.insert(v1.end(), v2.begin(), v2.end());
        return v1;
    }
};