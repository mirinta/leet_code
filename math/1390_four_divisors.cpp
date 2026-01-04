#include <vector>

/**
 * Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four
 * divisors. If there is no such integer in the array, return 0.
 *
 * ! 1 <= nums.length <= 10^4
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    int sumFourDivisors(std::vector<int>& nums)
    {
        int result = 0;
        for (const auto& v : nums) {
            result += helper(v);
        }
        return result;
    }

private:
    int helper(int x)
    {
        int count = 0;
        int sum = 0;
        for (long long i = 1; i * i <= x; ++i) {
            if (x % i)
                continue;

            const long long j = x / i;
            sum += i + (i != j) * j;
            count += 1 + (i != j);
        }
        return count == 4 ? sum : 0;
    }
};
