#include <vector>

/**
 * You are given an integer array nums containing positive integers. We define a function encrypt
 * such that encrypt(x) replaces every digit in x with the largest digit in x. For example,
 * encrypt(523) = 555 and encrypt(213) = 333.
 *
 * Return the sum of encrypted elements.
 *
 * ! 1 <= nums.length <= 50
 * ! 1 <= nums[i] <= 1000
 */

class Solution {
public:
    int sumOfEncryptedInt(std::vector<int>& nums)
    {
        int result = 0;
        for (const auto& val : nums) {
            const int max = getMax(val);
            result += generate(max, val);
        }
        return result;
    }

private:
    int getMax(int val)
    {
        int max = 0;
        while (val) {
            max = std::max(max, val % 10);
            val /= 10;
        }
        return max;
    }

    int generate(int max, int val)
    {
        int result = 0;
        while (val) {
            result = result * 10 + max;
            val /= 10;
        }
        return result;
    }
};