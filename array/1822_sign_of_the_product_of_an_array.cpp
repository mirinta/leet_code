#include <vector>

/**
 * There is a function "signFunc(x)" that returns:
 *
 * - 1 if x is positive
 *
 * - -1 if x is negative
 *
 * - 0 if x is equal to 0
 *
 * You are given an integer array "nums". Let "product" be the product of all values in the array
 * "nums".
 *
 * Return "signFunc(product)".
 */

class Solution {
public:
    int arraySign(const std::vector<int>& nums)
    {
        int negativeCount = 0;
        for (const auto& i : nums) {
            if (i == 0)
                return 0;

            if (i < 0) {
                negativeCount++;
            }
        }
        return negativeCount % 2 == 0 ? 1 : -1;
    }
};