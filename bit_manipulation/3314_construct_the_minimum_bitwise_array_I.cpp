#include <vector>

/**
 * You are given an array nums consisting of n prime integers.
 *
 * You need to construct an array ans of length n, such that, for each index i, the bitwise OR of ans[i] and ans[i] + 1
 * is equal to nums[i], i.e. ans[i] OR (ans[i] + 1) == nums[i].
 *
 * Additionally, you must minimize each value of ans[i] in the resulting array.
 *
 * If it is not possible to find such a value for ans[i] that satisfies the condition, then set ans[i] = -1.
 *
 * ! 1 <= nums.length <= 100
 * ! 2 <= nums[i] <= 1000
 * ! nums[i] is a prime number.
 */

class Solution {
public:
    std::vector<int> minBitwiseArray(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result;
        result.reserve(n);
        for (const auto& v : nums) {
            result.push_back(solve(v));
        }
        return result;
    }

private:
    long long solve(int n)
    {
        int i = 0;
        while (i < 32 && ((n >> i) & 1)) {
            i++;
        }
        i--;
        if (i < 0)
            return -1;

        return n & (n - (1 << i));
    }
};
