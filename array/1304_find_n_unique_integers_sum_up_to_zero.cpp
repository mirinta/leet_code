#include <vector>

/**
 * Given an integer n, return any array containing n unique integers such that they add up to 0.
 *
 * ! 1 <= n <= 1000
 */

class Solution
{
public:
    std::vector<int> sumZero(int n)
    {
        std::vector<int> result;
        result.reserve(n);
        for (int i = 1; i <= n / 2; ++i) {
            result.push_back(i);
            result.push_back(-i);
        }
        if (n % 2) {
            result.push_back(0);
        }
        return result;
    }
};