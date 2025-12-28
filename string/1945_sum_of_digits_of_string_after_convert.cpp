#include <string>

/**
 * You are given a string s consisting of lowercase English letters, and an integer k.
 *
 * First, convert s into an integer by replacing each letter with its position in the alphabet
 * (i.e., replace 'a' with 1, 'b' with 2, ..., 'z' with 26). Then, transform the integer by
 * replacing it with the sum of its digits. Repeat the transform operation k times in total.
 *
 * For example, if s = "zbax" and k = 2, then the resulting integer would be 8 by the following
 * operations:
 *
 * - Convert: "zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124
 *
 * - Transform #1: 262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17
 *
 * - Transform #2: 17 ➝ 1 + 7 ➝ 8
 *
 * Return the resulting integer after performing the operations described above.
 *
 * ! 1 <= s.length <= 100
 * ! 1 <= k <= 10
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int getLucky(std::string s, int k)
    {
        int result = 0;
        for (const auto& c : s) {
            result += sumDigits(c - 'a' + 1);
        }
        for (int i = 0; i < k - 1; ++i) {
            result = sumDigits(result);
        }
        return result;
    }

private:
    int sumDigits(int val)
    {
        int sum = 0;
        while (val) {
            sum += val % 10;
            val /= 10;
        }
        return sum;
    }
};
