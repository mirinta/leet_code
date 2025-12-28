#include <vector>

/**
 * Given an array of integer "arr", return true if and only if it is a valid mountain array.
 *
 * Recall that "arr" is a mountain array if and only if:
 *
 * - arr.length >= 3
 *
 * - There exists some i with 0 < i < arr.length - 1 such that:
 *
 * - arr[0] < arr[1] < ... < arr[i - 1] < arr[i], and
 *
 * - arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
 */

class Solution {
public:
    bool validMountainArray(const std::vector<int>& arr)
    {
        if (arr.size() < 3)
            return false;

        int low = 0;
        int high = arr.size() - 1;
        while (low < arr.size() - 1 && arr[low + 1] > arr[low]) {
            low++;
        }
        while (high >= 1 && arr[high - 1] > arr[high]) {
            high--;
        }
        return low == high && low < arr.size() - 1 && low > 0;
    }
};