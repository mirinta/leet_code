/**
 * You are given two positive integers n and k. A factor of an integer n is defined as an integer i
 * where n % i == 0.
 *
 * Consider a list of all factors of n sorted in ascending order, return the kth factor in this list
 * or return -1 if n has less than k factors.
 *
 * ! 1 <= k <= n <= 1000
 *
 * ! Could you solve this problem in less than O(n) complexity?
 */

class Solution {
public:
    int kthFactor(int n, int k)
    {
        return approach2(n, k);
    }

private:
    // TC = O(sqrt(N)), SC = O(1)
    int approach2(int n, int k)
    {
        int factor = 1;
        for (; factor * factor <= n; ++factor) {
            if (n % factor == 0 && --k == 0)
                return factor;
        }
        while (factor * factor >= n) {
            factor--;
        }
        for (; factor > 0; --factor) {
            if (n % factor == 0 && --k == 0)
                return n / factor;
        }
        return -1;
    }

    // TC = O(N), SC = O(1)
    int approach1(int n, int k)
    {
        for (int i = 1; i <= n; ++i) {
            if (n % i == 0 && --k == 0)
                return i;
        }
        return -1;
    }
};