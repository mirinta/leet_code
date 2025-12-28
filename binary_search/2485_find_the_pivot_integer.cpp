
/**
 * Given a positive integer n, find the pivot integer x such that:
 *
 * - The sum of all elements between 1 and x inclusively equals the sum of all elements between x
 * and n inclusively.
 *
 * Return the pivot integer x. If no such integer exists, return -1. It is guaranteed that there
 * will be at most one pivot index for the given input.
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    int pivotInteger(int n)
    {
        // 1 + ... + x = x + ... + n
        // 2 * (1 + ... + x) = total + x
        // (1 + x)x - x = total
        // x^2 = total
        const int total = (1 + n) * n / 2;
        int lo = 1;
        int hi = n;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int square = mid * mid;
            if (square == total)
                return mid;

            if (square > total) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return -1;
    }
};