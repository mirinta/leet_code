#include <vector>

/**
 * Given an integer array arr, remove a subarray (can be empty) from arr such that the remaining
 * elements in arr are non-decreasing.
 *
 * Return the length of the shortest subarray to remove.
 *
 * A subarray is a contiguous subsequence of the array.
 *
 * ! 1 <= arr.length <= 10^5
 * ! 0 <= arr[i] <= 10^9
 */

class Solution {
public:
    int findLengthOfShortestSubarray(std::vector<int>& arr)
    {
        // similar to LC.2972
        const int n = arr.size();
        // find the largest i such that arr[0:i] is non-decreasing
        int i = 0;
        while (i + 1 < n && arr[i] <= arr[i + 1]) {
            i++;
        }
        // if the original arr is already non-decreasing,
        // we do not need to remove any elements
        // thus, length of the shortest subarray to remove = 0
        if (i == n - 1)
            return 0;

        // since arr[0:i] is non-decreasing,
        // remove arr[i+1:n-1], the remaining is arr[0:i] which is non-decreasing
        // remove arr[i:n-1], the remaining is arr[0:i-1] which is non-decreasing
        // ...
        // remove arr[1:n-1], the remaining is arr[0:0] which is non-decreasing
        // the shortest subarray to remove is arr[i+1:n-1], its length is n-i-1
        int result = n - i - 1;
        // given arr[j],
        // if arr[j:n-1] is non-decreasing and arr[j] >= arr[i]
        // then we can remove arr[i+1:j-1] to make the remaining elements non-decreasing
        for (int j = n - 1; j > 0; --j) {
            while (i >= 0 && arr[i] > arr[j]) {
                i--;
            }
            result = std::min(result, j - i - 1);
            if (arr[j] < arr[j - 1])
                break;
        }
        return result;
    }
};