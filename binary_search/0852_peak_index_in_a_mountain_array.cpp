#include <vector>

/**
 * An array arr a mountain if the following properties hold:
 *
 * - arr.length >= 3
 *
 * - There exists some i with 0 < i < arr.length - 1 such that:
 *   arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
 *   arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 *
 * Given a mountain array arr, return the index i such that arr[0] < arr[1] < ... < arr[i - 1] <
 * arr[i] > arr[i + 1] > ... > arr[arr.length - 1].
 *
 * ! You must solve it in O(log(arr.length)) time complexity.
 *
 * ! 3 <= arr.length <= 10^5
 * ! 0 <= arr[i] <= 10^6
 * ! arr is guaranteed to be a mountain array.
 */

class Solution {
public:
    int peakIndexInMountainArray(std::vector<int>& arr)
    {
        // [...MID-1] MID [MID+1...]
        int lo = 0;
        int hi = arr.size() - 1;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (arr[mid + 1] > arr[mid]) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
};