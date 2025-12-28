#include <vector>

/**
 * Given an array of integers arr and two integers k and threshold, return the number of sub-arrays
 * of size k and average greater than or equal to threshold.
 *
 * ! 1 <= arr.length <= 10^5
 * ! 1 <= arr[i] <= 10^4
 * ! 1 <= k <= arr.length
 * ! 0 <= threshold <= 10^4
 */

class Solution {
public:
    int numOfSubarrays(std::vector<int>& arr, int k, int threshold)
    {
        const int n = arr.size();
        int sum = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += arr[right];
            if (right - left + 1 > k) {
                sum -= arr[left++];
            }
            if (right - left + 1 == k && sum >= threshold * k) {
                result++;
            }
        }
        return result;
    }
};