#include <numeric>

/**
 * We have two arrays arr1 and arr2 which are initially empty. You need to add positive integers to
 * them such that they satisfy all the following conditions:
 *
 * - arr1 contains uniqueCnt1 distinct positive integers, each of which is not divisible by
 * divisor1.
 *
 * - arr2 contains uniqueCnt2 distinct positive integers, each of which is not divisible by
 * divisor2.
 *
 * - No integer is present in both arr1 and arr2.
 *
 * Given divisor1, divisor2, uniqueCnt1, and uniqueCnt2, return the minimum possible maximum integer
 * that can be present in either array.
 *
 * ! 2 <= divisor1, divisor2 <= 10^5
 * ! 1 <= uniqueCnt1, uniqueCnt2 < 10^9
 * ! 2 <= uniqueCnt1 + uniqueCnt2 <= 10^9
 */

class Solution {
public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2)
    {
        int lo = 1;
        int hi = INT_MAX;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, divisor1, divisor2, uniqueCnt1, uniqueCnt2)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    // check if it is possible to select numbers in [1:n] such that
    // arr1 contains >= uniqueCnt1 distinct integers which are not divisible by divisor1
    // arr2 contains >= uniqueCnt1 distinct integers which are not divisible by divisor2
    // arr1 and arr2 are different
    bool isValid(long long n, long long divisor1, long long divisor2, long long uniqueCnt1, long long uniqueCnt2)
    {
        // A = num of distinct integers which are not divisible by divisor1
        const long long A = n - n / divisor1;
        if (A < uniqueCnt1)
            return false;

        // B = num of distinct integers which are not divisible by divisor2
        const long long B = n - n / divisor2;
        if (B < uniqueCnt2)
            return false;

        // C = num of distinct integers which are not divisible by divisor1 and divisor2
        const long long C = n - (n / divisor1 + n / divisor2 - n / std::lcm(divisor1, divisor2));
        return A + B - C >= uniqueCnt1 + uniqueCnt2;
    }
};