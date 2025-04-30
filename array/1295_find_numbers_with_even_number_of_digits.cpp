#include <vector>

/**
 * Given an array "nums" of integers, return how many of them contain an even number of digits.
 *
 * ! 1 <= nums.length <= 500
 * ! 1 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int findNumbers(std::vector<int>& nums)
    {
        int result = 0;
        for (const auto& val : nums) {
            result += isValid(val);
        }
        return result;
    }

private:
    bool isValid(int n)
    {
        if (n == 0)
            return false;

        int count = 0;
        while (n) {
            count++;
            n /= 10;
        }
        return count % 2 == 0;
    }
};
