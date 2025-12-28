#include <vector>

/**
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product
 * of all the elements of nums except nums[i].
 *
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 *
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 *
 * ! 2 <= nums.length <= 10^5
 * ! -30 <= nums[i] <= 30
 * ! The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 */

class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        // result[n-1] = nums[0]*...*nums[n-2]
        // result[n-2] = nums[0]*...*nums[n-3]*nums[n-1]
        // result[n-3] = nums[0]*...*nums[n-4]*nums[n-2]*nums[n-1]
        // ...
        const int n = nums.size();
        std::vector<int> result(n, 1);
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] * nums[i - 1];
        }
        for (int i = n - 1, base = 1; i >= 0; --i) {
            result[i] *= base;
            base *= nums[i];
        }
        return result;
    }

    std::vector<int> approach1(const std::vector<int>& nums)
    {
        // prefix[i] = nums[0]*...*nums[i-1]
        // suffix[i] = nums[n-1]*...*nums[i+1]
        const int n = nums.size();
        std::vector<int> prefix(n, 1);
        for (int i = 1; i < n; ++i) {
            prefix[i] = prefix[i - 1] * nums[i - 1];
        }
        std::vector<int> suffix(n, 1);
        for (int i = n - 2; i >= 0; --i) {
            suffix[i] = suffix[i + 1] * nums[i + 1];
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = prefix[i] * suffix[i];
        }
        return result;
    }
};