/**
 * Given two non-negative integers "low" and "high". Return the count of odd numbers between low and
 * high (inclusive).
 */

class Solution {
public:
    int countOdds(int low, int high)
    {
        // if both low and high are odd numbers,
        // consider an AP sequence with common difference of 2,
        // the first term is low and the last term is high,
        // the problem is to count the number of terms of this sequence
        if (!(low & 1)) {
            low++;
        }
        if (!(high & 1)) {
            high--;
        }
        return low > high ? 0 : (high - low) / 2 + 1;
    }
};