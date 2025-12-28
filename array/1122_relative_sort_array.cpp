#include <algorithm>
#include <vector>

/**
 * Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are
 * also in arr1.
 *
 * Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in
 * arr2. Elements that do not appear in arr2 should be placed at the end of arr1 in ascending order.
 *
 * ! 1 <= arr1.length, arr2.length <= 1000
 * ! 0 <= arr1[i], arr2[i] <= 1000
 * ! All the elements of arr2 are distinct.
 * ! Each arr2[i] is in arr1.
 */

class Solution {
public:
    std::vector<int> relativeSortArray(std::vector<int>& arr1, std::vector<int>& arr2)
    {
        const int max = *std::max_element(arr1.begin(), arr1.end());
        std::vector<int> bucket(max + 1, 0);
        for (const auto& val : arr1) {
            bucket[val]++;
        }
        std::vector<int> result;
        result.reserve(arr1.size());
        for (const auto& val : arr2) {
            result.insert(result.end(), bucket[val], val);
            bucket[val] = 0;
        }
        for (int i = 0; i <= max; ++i) {
            if (bucket[i] != 0) {
                result.insert(result.end(), bucket[i], i);
            }
        }
        return result;
    }
};