#include <vector>

/**
 * Given a sorted integer array "arr", two integers k and x, return the k closest integers to x in
 * the array. The result should also be sorted in ascending order.
 *
 * An integer a is closer to x than an integer b if:
 *
 * - |a - x| < |b - x|, or
 *
 * - |a - x| == |b - x| and a < b
 *
 * ! 1 <= k <= arr.length
 * ! 1 <= arr.length <= 10^4
 * ! arr is sorted in ascending order.
 * ! -10^4 <= arr[i], x <= 10^4
 */

class Solution {
public:
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
    {
        const int n = arr.size();
        const int index = std::lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int left = index - 1;
        int right = index;
        while (right - left - 1 < k) {
            if (right == n || (left >= 0 && x - arr[left] <= arr[right] - x)) {
                left--;
            } else {
                right++;
            }
        }
        return {arr.begin() + left + 1, arr.begin() + right};
    }
};