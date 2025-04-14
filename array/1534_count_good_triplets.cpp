#include <vector>

/**
 * Given an array of integers arr, and three integers a, b and c. You need to find the number of
 * good triplets.
 *
 * A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:
 *
 * - 0 <= i < j < k < arr.length
 *
 * - |arr[i] - arr[j]| <= a
 *
 * - |arr[j] - arr[k]| <= b
 *
 * - |arr[i] - arr[k]| <= c
 *
 * Where |x| denotes the absolute value of x.
 *
 * Return the number of good triplets.
 *
 * ! 3 <= arr.length <= 100
 * ! 0 <= arr[i] <= 1000
 * ! 0 <= a, b, c <= 1000
 */

class Solution
{
public:
    int countGoodTriplets(std::vector<int>& arr, int a, int b, int c)
    {
        const int n = arr.size();
        int result = 0;
        auto isValid = [&](int i, int j, int k) {
            return std::abs(arr[i] - arr[j]) <= a && std::abs(arr[j] - arr[k]) <= b &&
                   std::abs(arr[i] - arr[k]) <= c;
        };
        for (int j = 1; j < n - 1; ++j) {
            for (int i = j - 1; i >= 0; --i) {
                for (int k = j + 1; k < n; ++k) {
                    result += isValid(i, j, k);
                }
            }
        }
        return result;
    }
};
