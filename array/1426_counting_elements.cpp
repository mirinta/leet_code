#include <unordered_set>
#include <vector>

/**
 * Given an integer array arr, count how many elements x there are, such that x + 1 is also in arr.
 * If there are duplicates in arr, count them separately.
 *
 * ! 1 <= arr.length <= 1000
 * ! 0 <= arr[i] <= 1000
 */

class Solution {
public:
    int countElements(std::vector<int>& arr)
    {
        std::unordered_set<int> set(arr.begin(), arr.end());
        int result = 0;
        for (const auto& val : arr) {
            if (set.count(val + 1)) {
                result++;
            }
        }
        return result;
    }
};
