#include <numeric>
#include <vector>

/**
 * In some array arr, the values were in arithmetic progression: the values arr[i + 1] - arr[i] are
 * all equal for every 0 <= i < arr.length - 1.
 *
 * A value from arr was removed that was not the first or last value in the array.
 *
 * Given arr, return the removed value.
 *
 * ! 3 <= arr.length <= 1000
 * ! 0 <= arr[i] <= 10^5
 * ! The given array is guaranteed to be a valid array.
 */

class Solution {
public:
    int missingNumber(std::vector<int>& arr)
    {
        return approach2(arr);
    }

private:
    int approach2(const std::vector<int>& arr)
    {
        const int n = arr.size();
        const int diff = (arr.back() - arr.front()) / n;
        int lo = 0;
        int hi = n - 1;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            const int expected = arr.front() + mid * diff;
            if (arr[mid] == expected) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return arr.front() + lo * diff;
    }

    // time O(N), space O(1)
    int approach1(const std::vector<int>& arr)
    {
        // there is only one removed element
        const int n = arr.size();
        const int expectedSum = (arr.back() + arr.front()) * (n + 1) / 2;
        return expectedSum - std::accumulate(arr.begin(), arr.end(), 0);
    }
};