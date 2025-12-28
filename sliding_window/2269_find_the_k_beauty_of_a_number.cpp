#include <string>

/**
 * The k-beauty of an integer num is defined as the number of substrings of num when it is read as a
 * string that meet the following conditions:
 *
 * - It has a length of k.
 *
 * - It is a divisor of num.
 *
 * Given integers num and k, return the k-beauty of num.
 *
 * Note:
 *
 * - Leading zeros are allowed.
 *
 * - 0 is not a divisor of any value.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * ! 1 <= num <= 10^9
 * ! 1 <= k <= num.length (taking num as a string)
 */

class Solution {
public:
    int divisorSubstrings(int num, int k)
    {
        const std::string s = std::to_string(num);
        int result = 0;
        for (int i = 0; i <= s.size() - k; ++i) {
            const int val = std::stoi(s.substr(i, k));
            if (val != 0 && num % val == 0) {
                result++;
            }
        }
        return result;
    }
};