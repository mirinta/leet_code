#include <vector>

/**
 * Numbers can be regarded as the product of their factors.
 *
 * - For example, 8 = 2 x 2 x 2 = 2 x 4.
 *
 * Given an integer n, return all possible combinations of its factors. You may return the answer in
 * any order.
 *
 * Note that the factors should be in the range [2, n - 1].
 *
 * ! 1 <= n <= 10^7
 */

class Solution {
public:
    std::vector<std::vector<int>> getFactors(int n)
    {
        std::vector<int> factors;
        backtrack(factors, n);
        return result;
    }

private:
    std::vector<std::vector<int>> result;

    void backtrack(std::vector<int>& factors, int n)
    {
        for (int f = factors.empty() ? 2 : factors.back(); f <= n / f; ++f) {
            if (n % f != 0)
                continue;

            factors.push_back(f);
            factors.push_back(n / f);
            result.push_back(factors);
            factors.pop_back();
            backtrack(factors, n / f);
            factors.pop_back();
        }
    }
};