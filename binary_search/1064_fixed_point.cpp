#include <vector>

/**
 * Given an array of distinct integers arr, where arr is sorted in ascending order, return the
 * smallest index i that satisfies arr[i] == i. If there is no such index, return -1.
 *
 * ! 1 <= arr.length < 10^4
 * ! -10^9 <= arr[i] <= 10^9
 */

class Solution {
public:
    int fixedPoint(std::vector<int>& arr)
    {
        const int n = arr.size();
        int lo = 0;
        int hi = n - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (arr[mid] >= mid) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo == n || arr[lo] != lo ? -1 : lo;
    }
};