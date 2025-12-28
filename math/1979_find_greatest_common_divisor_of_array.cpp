#include <vector>

/**
 * Given an integer array nums, return the greatest common divisor of the smallest number and
 * largest number in nums.
 *
 * The greatest common divisor of two numbers is the largest positive integer that evenly divides
 * both numbers.
 *
 * ! 2 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 */

class Solution {
public:
    int findGCD(std::vector<int>& nums)
    {
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& val : nums) {
            min = std::min(min, val);
            max = std::max(max, val);
        }
        return gcd(min, max);
    }

private:
    int gcd(int n1, int n2)
    {
        while (n2) {
            const int backup = n2;
            n2 = n1 % n2;
            n1 = backup;
        }
        return n1;
    }
};