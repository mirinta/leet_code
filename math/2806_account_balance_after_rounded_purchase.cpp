#include <cmath>
#include <utility>

/**
 * Initially, you have a bank account balance of 100 dollars.
 *
 * You are given an integer purchaseAmount representing the amount you will spend on a purchase in
 * dollars.
 *
 * At the store where you will make the purchase, the purchase amount is rounded to the nearest
 * multiple of 10. In other words, you pay a non-negative amount, roundedAmount, such that
 * roundedAmount is a multiple of 10 and abs(roundedAmount - purchaseAmount) is minimized.
 *
 * If there is more than one nearest multiple of 10, the largest multiple is chosen.
 *
 * Return an integer denoting your account balance after making a purchase worth purchaseAmount
 * dollars from the store.
 *
 * Note: 0 is considered to be a multiple of 10 in this problem.
 *
 * ! 0 <= purchaseAmount <= 100
 */

class Solution {
public:
    int accountBalanceAfterPurchase(int purchaseAmount)
    {
        const int r = purchaseAmount % 10;
        const int case1 = purchaseAmount - r;
        const int case2 = purchaseAmount + 10 - r;
        const int diff = std::abs(case1 - purchaseAmount) - std::abs(case2 - purchaseAmount);
        if (diff >= 0)
            return 100 - case2;

        return 100 - case1;
    }
};