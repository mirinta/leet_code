#include <vector>

/**
 * Given an array of integers citations where citations[i] is the number of citations a researcher
 * received for their ith paper and citations is sorted in ascending order, return the researcher's
 * h-index.
 *
 * According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value
 * of h such that the given researcher has published at least h papers that have each been cited at
 * least h times.
 *
 * You must write an algorithm that runs in logarithmic time.
 *
 * ! n == citations.length
 * ! 1 <= n <= 10^5
 * ! 0 <= citations[i] <= 1000
 * ! citations is sorted in ascending order.
 */

class Solution {
public:
    int hIndex(std::vector<int>& citations)
    {
        // find the smallest x such that
        // citations[x] >= n - x
        // then h = n - x
        const int n = citations.size();
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (citations[mid] >= n - mid) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return n - lo;
    }
};