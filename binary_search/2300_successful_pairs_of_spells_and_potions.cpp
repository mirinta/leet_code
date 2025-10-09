#include <algorithm>
#include <cmath>
#include <vector>

/**
 * You are given two positive integer arrays spells and potions, of length n and m respectively,
 * where spells[i] represents the strength of the ith spell and potions[j] represents the strength
 * of the jth potion.
 *
 * You are also given an integer success. A spell and potion pair is considered successful if the
 * product of their strengths is at least success.
 *
 * Return an integer array pairs of length n where pairs[i] is the number of potions that will form
 * a successful pair with the ith spell.
 *
 * ! n == spells.length
 * ! m == potions.length
 * ! 1 <= n, m <= 10^5
 * ! 1 <= spells[i], potions[i] <= 10^5
 * ! 1 <= success <= 10^10
 */

class Solution
{
public:
    std::vector<int> successfulPairs(std::vector<int>& spells, std::vector<int>& potions,
                                     long long success)
    const int n = spells.size();
    std::sort(potions.begin(), potions.end());
    std::vector<int> result(n, 0);
    for (int i = 0; i < n; ++i) {
        const long long target = std::ceil(1.0 * success / spells[i]);
        auto iter = std::lower_bound(potions.begin(), potions.end(), target);
        result[i] = std::distance(iter, potions.end());
    }
    return result;
};
