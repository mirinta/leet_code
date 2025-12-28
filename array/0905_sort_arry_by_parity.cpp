#include <vector>

/**
 * Given an integer array nums, move all the even integers at the beginning of the array followed by
 * all the odd integers.
 *
 * Return any array that satisfies this condition.
 *
 * ! 1 <= nums.length <= 5000
 * ! 0 <= nums[i] <= 5000
 */

class Solution {
public:
    std::vector<int> sortArrayByParity(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // one-pass, in-place, time O(N), space O(1)
    std::vector<int> approach3(std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return nums;

        const int n = nums.size();
        int even = 0;
        int odd = n - 1;
        while (true) {
            while (even < n && nums[even] % 2 == 0) {
                even++;
            }
            while (odd >= 0 && nums[odd] % 2 != 0) {
                odd--;
            }
            if (even >= odd)
                break;

            std::swap(nums[even], nums[odd]);
        }
        return nums;
    }

    // one-pass, time O(N), space O(N)
    std::vector<int> approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        int even = 0;
        int odd = n - 1;
        for (const auto& val : nums) {
            if (val % 2 == 0) {
                result[even++] = val;
            } else {
                result[odd--] = val;
            }
        }
        return result;
    }

    // two-pass, time O(N), space O(N)
    std::vector<int> approach1(const std::vector<int>& nums)
    {
        std::vector<int> result;
        result.reserve(nums.size());
        for (const auto& val : nums) {
            if (val % 2 == 0) {
                result.push_back(val);
            }
        }
        for (const auto& val : nums) {
            if (val % 2 != 0) {
                result.push_back(val);
            }
        }
        return result;
    }
};
