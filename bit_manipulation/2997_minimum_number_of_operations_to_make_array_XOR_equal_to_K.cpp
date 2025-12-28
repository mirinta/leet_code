#include <array>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and a positive integer k.
 *
 * You can apply the following operation on the array any number of times:
 *
 * Choose any element of the array and flip a bit in its binary representation. Flipping a bit means
 * changing a 0 to 1 or vice versa. Return the minimum number of operations required to make the
 * bitwise XOR of all elements of the final array equal to k.
 *
 * Note that you can flip leading zero bits in the binary representation of elements. For example,
 * for the number (101)2 you can flip the fourth bit and obtain (1101)2.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^6
 * ! 0 <= k <= 10^6
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    int approach2(const std::vector<int>& nums, int k)
    {
        // let XOR = bitwise XOR of all elements of nums
        // if k[i] = 1, we need odd num of bits = 1
        // - if we have even num of bits = 1, then XOR[i] = 0
        // if k[i] = 0, we need even num of bits = 1
        // - if we have odd num of bits = 1, then XOR[i] = 1
        int XOR = 0;
        for (const auto& val : nums) {
            XOR ^= val;
        }
        return numOfBinaryOnes(XOR ^ k);
    }

    int numOfBinaryOnes(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }

    int approach1(const std::vector<int>& nums, int k)
    {
        // k[i] = 1, we need odd num of bits = 1
        // k[i] = 0, we need even num of bits = 1
        std::array<int, 32> count{};
        for (const auto& val : nums) {
            for (int i = 0; i < 32; ++i) {
                count[i] += (val >> i) & 1;
            }
        }
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            if ((k >> i) & 1) {
                result += count[i] % 2 == 0;
            } else {
                result += count[i] % 2 != 0;
            }
        }
        return result;
    }
};