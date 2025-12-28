#include <vector>

/**
 * There is a bookstore owner that has a store open for n minutes. Every minute, some number of
 * customers enter the store. You are given an integer array customers of length n where
 * customers[i] is the number of the customer that enters the store at the start of the ith minute
 * and all those customers leave after the end of that minute.
 *
 * On some minutes, the bookstore owner is grumpy. You are given a binary array grumpy where
 * grumpy[i] is 1 if the bookstore owner is grumpy during the ith minute, and is 0 otherwise.
 *
 * When the bookstore owner is grumpy, the customers of that minute are not satisfied, otherwise,
 * they are satisfied.
 *
 * The bookstore owner knows a secret technique to keep themselves not grumpy for minutes
 * consecutive minutes, but can only use it once.
 *
 * Return the maximum number of customers that can be satisfied throughout the day.
 *
 * ! n == customers.length == grumpy.length
 * ! 1 <= minutes <= n <= 2 * 10^4
 * ! 0 <= customers[i] <= 1000
 * ! grumpy[i] is either 0 or 1.
 */

class Solution {
public:
    int maxSatisfied(std::vector<int>& customers, std::vector<int>& grumpy, int minutes)
    {
        const int n = customers.size();
        int total = 0;
        for (int i = 0; i < n; ++i) {
            if (!grumpy[i]) {
                total += customers[i];
            }
        }
        int result = 0;
        for (int left = 0, right = 0, sum1 = 0, sum2 = 0; right < n; ++right) {
            sum1 += customers[right];
            sum2 += customers[right] * (1 - grumpy[right]);
            if (right - left + 1 > minutes) {
                sum1 -= customers[left];
                sum2 -= customers[left] * (1 - grumpy[left]);
                left++;
            }
            if (right - left + 1 == minutes) {
                result = std::max(result, sum1 + total - sum2);
            }
        }
        return result;
    }
};