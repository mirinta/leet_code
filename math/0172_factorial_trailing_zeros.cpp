/**
 * Given an integer n, return the number of trailing zeroes in n!.
 *
 * Note that n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1.
 *
 * ! 0 <= n <= 10^4
 *
 * ! Follow up: Could you write a solution that works in logarithmic time complexity?
 */

class Solution {
public:
    int trailingZeroes(int n)
    {
        //  5! = 5*4*3*2*1          => #zeros=1
        // 10! = 10*9*...*6*(5!)    => #zeros=2
        // 15! = 15*14*...*11*(10!) => #zeros=3
        // 20! = 20*19*...*16*(15!) => #zeros=4
        int result = 0;
        while (n) {
            n /= 5;
            result += n;
        }
        return result;
    }
};