#include <vector>

/**
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n),
 * ans[i] is the number of 1's in the binary representation of i.
 *
 * ! 0 <= n <= 10^5
 *
 * ! Can you do it in linear time O(n) and possibly in a single pass?
 */

class Solution {
public:
    std::vector<int> countBits(int n)
    {
        return approach2(n);
    }

private:
    // TC = O(N), SC = O(N)
    std::vector<int> approach2(int n)
    {
        std::vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            result[i] = result[i & (i - 1)] + 1;
        }
        return result;
    }

    // TC = O(NlogN), SC = space O(N)
    std::vector<int> approach1(int n)
    {
        std::vector<int> result(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            result[i] = binaryOnes(i);
        }
        return result;
    }

    int binaryOnes(int val)
    {
        int result = 0;
        while (val) {
            result++;
            val &= (val - 1);
        }
        return result;
    }
};