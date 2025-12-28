#include <array>
#include <vector>

/**
 * You are given an array nums consisting of positive integers where all integers have the same
 * number of digits.
 *
 * The digit difference between two integers is the count of different digits that are in the same
 * position in the two integers.
 *
 * Return the sum of the digit differences between all pairs of integers in nums.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i] < 10^9
 * ! All integers in nums have the same number of digits.
 */

class Solution {
public:
    long long sumDigitDifferences(std::vector<int>& nums)
    {
        const int digits = numOfDigits(nums[0]);
        std::array<long long, 10> count{};
        long long result = 0;
        for (int i = 0; i < digits; ++i) {
            std::fill(count.begin(), count.end(), 0);
            for (auto& val : nums) {
                const int d = val % 10;
                for (int j = 0; j < 10; ++j) {
                    if (j == d)
                        continue;

                    result += count[j];
                }
                count[d]++;
                val /= 10;
            }
        }
        return result;
    }

private:
    long long numOfDigits(int n)
    {
        if (n == 0)
            return 1;

        long long result = 0;
        while (n) {
            result++;
            n /= 10;
        }
        return result;
    }
};