#include <numeric>
#include <vector>

/**
 * You have a set of integers s, which originally contains all the numbers from 1 to n.
 * Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the
 * set, which results in repetition of one number and loss of another number.
 *
 * You are given an integer array nums representing the data status of this set after the error.
 *
 * Find the number that occurs twice and the number that is missing and return them in the form of
 * an array.
 *
 * ! 2 <= nums.length <= 10^4
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    std::vector<int> findErrorNums(std::vector<int>& nums)
    {
        // indices are pigeon holes and elements are pigeons
        // nums[i] < 0 means the ith pigeon hole is occupied
        const int n = nums.size();
        const int expectedSum = (1 + n) * n / 2;
        const int actualSum = std::accumulate(nums.begin(), nums.end(), 0);
        for (const auto& val : nums) {
            const int absVal = std::abs(val);
            if (nums[absVal - 1] < 0)
                return {absVal, expectedSum - actualSum + absVal};

            nums[std::abs(val) - 1] *= -1;
        }
        return {};
    }
};