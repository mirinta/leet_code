/**
 * You have n coins and you want to build a staircase with these coins. The staircase consists of k
 * rows where the ith row has exactly i coins. The last row of the staircase may be incomplete.
 *
 * Given the integer n, return the number of complete rows of the staircase you will build.
 *
 * ! 1 <= n <= 2^31 - 1
 */

class Solution {
public:
    int arrangeCoins(int n)
    {
        int left = 1;
        int right = n;
        while (left <= right) {
            const long long mid = left + (right - left) / 2;
            const long long numOfCoins = (1 + mid) * mid / 2;
            if (numOfCoins > n) {
                right = mid - 1;
            } else if (numOfCoins < n) {
                left = mid + 1;
            } else {
                return mid;
            }
        }
        return right;
    }
};
