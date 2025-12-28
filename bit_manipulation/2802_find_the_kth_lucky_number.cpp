#include <string>

/**
 * We know that 4 and 7 are lucky digits. Also, a number is called lucky if it contains only lucky
 * digits.
 *
 * You are given an integer k, return the kth lucky number represented as a string.
 *
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    std::string kthLuckyNumber(int k)
    {
        // let binary 0 = 4 and binary 1 = 7
        // binary  10, remove leftmost 1 => binary  0 = 4
        // binary  11, remove leftmost 1 => binary  1 = 7
        // binary 100, remove leftmost 1 => binary 00 = 44
        // binary 101, remove leftmost 1 => binary 01 = 47
        // ...
        int binary = 2;
        while (k > 1) {
            binary += 1;
            k--;
        }
        std::string result;
        while (binary) {
            if (binary & 1) {
                result.push_back('7');
            } else {
                result.push_back('4');
            }
            binary >>= 1;
        }
        result.pop_back();
        std::reverse(result.begin(), result.end());
        return result;
    }
};