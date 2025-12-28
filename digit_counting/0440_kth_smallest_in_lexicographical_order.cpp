#include <utility>

/**
 * Given two integers n and k, return the kth lexicographically smallest integer in the range [1,
 * n].
 *
 * ! 1 <= k <= n <= 10^9
 */

class Solution {
public:
    int findKthNumber(int n, int k)
    {
        int num = 1;
        k--;
        while (k > 0) {
            const int count = helper(num, n);
            if (count <= k) {
                num++;
                k -= count;
            } else {
                num *= 10;
                k--;
            }
        }
        return num;
    }

private:
    // num of integers that start with prefix and are not greater than max
    int helper(long long prefix, long long max)
    {
        int count = 0;
        long long curr = prefix;
        long long next = prefix + 1;
        while (curr <= max) {
            count += std::min(next, max + 1) - curr;
            curr *= 10;
            next *= 10;
        }
        return count;
    }
};
