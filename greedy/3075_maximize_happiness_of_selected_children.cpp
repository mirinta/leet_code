#include <algorithm>
#include <vector>

/**
 * You are given an array happiness of length n, and a positive integer k.
 *
 * There are n children standing in a queue, where the ith child has happiness value happiness[i].
 * You want to select k children from these n children in k turns.
 *
 * In each turn, when you select a child, the happiness value of all the children that have not been
 * selected till now decreases by 1. Note that the happiness value cannot become negative and gets
 * decremented only if it is positive.
 *
 * Return the maximum sum of the happiness values of the selected children you can achieve by
 * selecting k children.
 *
 * ! 1 <= n == happiness.length <= 2 * 10^5
 * ! 1 <= happiness[i] <= 10^8
 * ! 1 <= k <= n
 */

class Solution {
public:
    long long maximumHappinessSum(std::vector<int>& happiness, int k)
    {
        std::sort(happiness.begin(), happiness.end(), std::greater<>());
        long long result = 0;
        for (int i = 0; i < k; ++i) {
            if (happiness[i] <= i)
                break;

            result += happiness[i] - i;
        }
        return result;
    }
};