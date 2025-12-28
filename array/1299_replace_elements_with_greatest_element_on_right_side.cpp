#include <vector>

/**
 * Given an array "arr", replace every element in that array with the greatest element among the
 * elements to its right, and replace the last element with -1.
 *
 * After doing so, return the array.
 */

class Solution {
public:
    std::vector<int> replaceElements(std::vector<int>& arr)
    {
        if (arr.empty())
            return {};

        std::vector<int> result(arr.size(), arr.back());
        for (int i = arr.size() - 2; i >= 0; --i) {
            result[i] = std::max(result[i + 1], arr[i + 1]);
        }
        result.back() = -1;
        return result;
    }
};