#include <unordered_map>

/**
 * You are given an integer n.
 *
 * Each number from 1 to n is grouped according to the sum of its digits.
 *
 * Return the number of groups that have the largest size.
 *
 * ! 1 <= n <= 10^4
 */

class Solution {
public:
    int countLargestGroup(int n)
    {
        std::unordered_map<int, int> map;
        int maxSize = 0;
        for (int i = 1; i <= n; ++i) {
            const int sum = helper(i);
            map[sum]++;
            maxSize = std::max(maxSize, map[sum]);
        }
        int result = 0;
        for (const auto& [sum, count] : map) {
            result += count == maxSize;
        }
        return result;
    }

private:
    int helper(int x)
    {
        int sum = 0;
        while (x) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }
};
