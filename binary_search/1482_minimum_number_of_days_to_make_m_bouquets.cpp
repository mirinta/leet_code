#include <algorithm>
#include <vector>

/**
 * You are given an integer array bloomDay, an integer m and an integer k.
 *
 * You want to make m bouquets. To make a bouquet, you need to use k adjacent flowers from the
 * garden.
 *
 * The garden consists of n flowers, the ith flower will bloom in the bloomDay[i] and then can be
 * used in exactly one bouquet.
 *
 * Return the minimum number of days you need to wait to be able to make m bouquets from the garden.
 * If it is impossible to make m bouquets return -1.
 *
 * ! bloomDay.length == n
 * ! 1 <= n <= 10^5
 * ! 1 <= bloomDay[i] <= 10^9
 * ! 1 <= m <= 10^6
 * ! 1 <= k <= n
 */

class Solution {
public:
    int minDays(std::vector<int>& bloomDay, int m, int k)
    {
        const int n = bloomDay.size();
        if (n / k < m)
            return -1;

        int lo = *std::min_element(bloomDay.begin(), bloomDay.end());
        int hi = *std::max_element(bloomDay.begin(), bloomDay.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, bloomDay, m, k)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int days, const std::vector<int>& bloomDay, int m, int k)
    {
        const int n = bloomDay.size();
        int i = 0;
        while (i < n) {
            while (i < n && bloomDay[i] > days) {
                i++;
            }
            int j = i + 1;
            while (j < std::min(n, i + k) && bloomDay[j] <= days) {
                j++;
            }
            if (j - i == k && --m == 0)
                return true;

            i = j;
        }
        return false;
    }
};