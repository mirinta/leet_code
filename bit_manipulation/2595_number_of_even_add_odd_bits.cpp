#include <vector>

/**
 * You are given a positive integer n.
 *
 * Let even denote the number of even indices in the binary representation of n (0-indexed) with
 * value 1.
 *
 * Let odd denote the number of odd indices in the binary representation of n (0-indexed) with
 * value 1.
 *
 * Return an integer array answer where answer = [even, odd].
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    std::vector<int> evenOddBit(int n)
    {
        int even = 0;
        int odd = 0;
        bool isEven = true;
        while (n) {
            even += isEven && (n & 1);
            odd += !isEven && (n & 1);
            n >>= 1;
            isEven = !isEven;
        }
        return {even, odd};
    }
};