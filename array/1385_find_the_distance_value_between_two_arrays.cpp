#include <algorithm>
#include <vector>

/**
 * Given two integer arrays arr1 and arr2, and the integer d, return the distance value between the two arrays.
 *
 * The distance value is defined as the number of elements arr1[i] such that there is not any element arr2[j] where
 * |arr1[i]-arr2[j]| <= d.
 *
 * ! 1 <= arr1.length, arr2.length <= 500
 * ! -1000 <= arr1[i], arr2[j] <= 1000
 * ! 0 <= d <= 100
 */

class Solution {
public:
    int findTheDistanceValue(std::vector<int>& arr1, std::vector<int>& arr2, int d)
    {
        std::sort(arr2.begin(), arr2.end());
        int result = 0;
        for (const auto& v : arr1) {
            auto iter = std::lower_bound(arr2.begin(), arr2.end(), v - d);
            if (iter == arr2.end() || *iter > v + d) {
                result++;
            }
        }
        return result;
    }
};
