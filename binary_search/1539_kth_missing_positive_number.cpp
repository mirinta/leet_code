#include <vector>

/**
 * Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
 *
 * Return the kth positive integer that is missing from this array.
 *
 * ! 1 <= arr.length <= 1000
 * ! 1 <= arr[i] <= 1000
 * ! 1 <= k <= 1000
 * ! arr[i] < arr[j] for 1 <= i < j <= arr.length
 */

class Solution {
public:
    int findKthPositive(std::vector<int>& arr, int k)
    {
        // given index = i, the expected value is i+1
        // nums[i]-(i+1) = how many missing numbers before nums[i]
        //    index:     0 1 2       3          4
        //     nums: [1] 2 3 4 [5,6] 7 [8,9,10] 11
        // expected:     1 2 3       4          6
        int lo = 0;
        int hi = arr.size() - 1;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            const int missingNums = arr[mid] - mid - 1;
            if (missingNums < k) {
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return lo + k; // arr[right] + k - (arr[right] - right - 1)
    }
};