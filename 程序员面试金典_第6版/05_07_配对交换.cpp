/**
 * 配对交换。编写程序，交换某个整数的奇数位和偶数位，尽量使用较少的指令（也就是说，位0与位1交换，位2与位3交换，以此类推）。
 *
 * ! num的范围在[0, 2^30 - 1]之间，不会发生整数溢出。
 */

class Solution {
public:
    int exchangeBits(int num)
    {
        // extract odd bits, mask = 1010,...,1010
        const int odd = num & 0xAAAAAAAA;
        // extract even bits, mask = 0101,...,0101
        const int even = num & 0x55555555;
        return (odd >> 1) | (even << 1);
    }
};