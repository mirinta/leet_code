#include <vector>

/**
 * Given an integer array arr, return true if there are three consecutive odd numbers in the array.
 * Otherwise, return false.
 *
 * ! 1 <= arr.length <= 1000
 * ! 1 <= arr[i] <= 1000
 */

class Solution {
public:
    bool threeConsecutiveOdds(std::vector<int>& arr)
    {
        int count = 0;
        for (const auto& val : arr) {
            if (val % 2) {
                count++;
            } else {
                count = 0;
            }
            if (count == 3)
                return true;
        }
        return false;
    }
};