#include <vector>

/**
 * Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
 *
 * You must write an algorithm that runs in O(n) time and uses O(1) extra space.
 *
 * ! 1 <= n <= 5 * 10^4
 */

class Solution {
public:
    std::vector<int> lexicalOrder(int n)
    {
        // n = 313
        // 1, 10, 100, 101~109,
        //    11, 110, 111~119,
        //    12, 120, 121~129,
        //        ...
        //    19, 190, 190~199,
        // 2, 20, 200, 201~201,
        //    21, 210, 211~219,
        //        ...
        //    29, 290, 291~299,
        // 3, 30, 300, 301~309,
        //    31, 310, 311~313,
        //    32~39,
        // 4, 40~49,
        // 5, 50~59,
        // ...
        // 9, 90~99
        std::vector<int> result{1};
        int i = 1;
        while (result.size() < n) {
            if (i * 10 <= n) {
                i *= 10;
            } else {
                while (i % 10 == 9 || i + 1 > n) {
                    i /= 10;
                }
                i++;
            }
            result.push_back(i);
        }
        return result;
    }
};
