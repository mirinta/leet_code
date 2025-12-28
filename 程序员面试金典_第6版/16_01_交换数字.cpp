#include <vector>

/**
 * 编写一个函数，不用临时变量，直接交换numbers = [a, b]中a与b的值。
 *
 * ! numbers.length == 2
 * ! -2147483647 <= numbers[i] <= 2147483647
 */

class Solution {
public:
    std::vector<int> swapNumbers(std::vector<int>& numbers)
    {
        const int temp = numbers[0] ^ numbers[1];
        return {temp ^ numbers[0], temp ^ numbers[1]};
    }
};