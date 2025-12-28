#include <numeric>
#include <vector>

/**
 * You have observations of n + m 6-sided dice rolls with each face numbered from 1 to 6. n of the
 * observations went missing, and you only have the observations of m rolls. Fortunately, you have
 * also calculated the average value of the n + m rolls.
 *
 * You are given an integer array rolls of length m where rolls[i] is the value of the ith
 * observation. You are also given the two integers mean and n.
 *
 * Return an array of length n containing the missing observations such that the average value of
 * the n + m rolls is exactly mean. If there are multiple valid answers, return any of them. If no
 * such array exists, return an empty array.
 *
 * The average value of a set of k numbers is the sum of the numbers divided by k.
 *
 * Note that mean is an integer, so the sum of the n + m rolls should be divisible by n + m.
 *
 * ! m == rolls.length
 * ! 1 <= n, m <= 10^5
 * ! 1 <= rolls[i], mean <= 6
 */

class Solution {
public:
    std::vector<int> missingRolls(std::vector<int>& rolls, int mean, int n)
    {
        const int m = rolls.size();
        const int diff = mean * (m + n) - std::accumulate(rolls.begin(), rolls.end(), 0);
        if (diff < n || diff > 6 * n)
            return {};

        std::vector<int> result(n, diff / n);
        for (int i = 0; i < diff % n; ++i) {
            result[i]++;
        }
        return result;
    }
};