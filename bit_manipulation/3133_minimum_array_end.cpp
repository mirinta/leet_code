/**
 * You are given two integers n and x. You have to construct an array of positive integers nums of
 * size n where for every 0 <= i < n - 1, nums[i + 1] is greater than nums[i], and the result of the
 * bitwise AND operation between all elements of nums is x.
 *
 * Return the minimum possible value of nums[n - 1].
 *
 * ! 1 <= n, x <= 10^8
 */

class Solution {
public:
    long long minEnd(int n, int x)
    {
        long long num = n - 1;
        long long result = x;
        for (int i = 0, j = 0; i < 64 && (num >> j); ++i) {
            if ((result >> i) & 1)
                continue;

            result |= ((num >> j) & 1) << i;
            j++;
        }
        return result;
    }
};