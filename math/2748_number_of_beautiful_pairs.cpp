#include <numeric>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. A pair of indices i, j where 0 <= i < j <
 * nums.length is called beautiful if the first digit of nums[i] and the last digit of nums[j] are
 * coprime.
 *
 * Return the total number of beautiful pairs in nums.
 *
 * Two integers x and y are coprime if there is no integer greater than 1 that divides both of them.
 * In other words, x and y are coprime if gcd(x, y) == 1, where gcd(x, y) is the greatest common
 * divisor of x and y.
 *
 * ! 2 <= nums.length <= 100
 * ! 1 <= nums[i] <= 9999
 * ! nums[i] % 10 != 0
 */

class Solution {
public:
    int countBeautifulPairs(std::vector<int>& nums)
    {
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            const int first = firstDigit(nums[i]);
            for (int j = i + 1; j < nums.size(); ++j) {
                const int last = nums[j] % 10;
                if (std::gcd(first, last) == 1) {
                    result++;
                }
            }
        }
        return result;
    }

private:
    int firstDigit(int val)
    {
        while (val >= 10) {
            val /= 10;
        }
        return val;
    }
};