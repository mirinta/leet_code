#include <vector>

/**
 * Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order, return a
 * sorted array of only the integers that appeared in all three arrays.
 *
 * ! 1 <= arr1.length, arr2.length, arr3.length <= 1000
 * ! 1 <= arr1[i], arr2[i], arr3[i] <= 2000
 */

class Solution {
public:
    std::vector<int> arraysIntersection(std::vector<int>& arr1, std::vector<int>& arr2, std::vector<int>& arr3)
    {
        int i = 0;
        int j = 0;
        int k = 0;
        std::vector<int> result;
        while (i < arr1.size() && j < arr2.size() && k < arr3.size()) {
            if (arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
                result.push_back(arr1[i]);
                i++;
                j++;
                k++;
            } else if (arr1[i] < arr2[j]) {
                i++;
            } else if (arr2[j] < arr3[k]) {
                j++;
            } else {
                k++;
            }
        }
        return result;
    }
};