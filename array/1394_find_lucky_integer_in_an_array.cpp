#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr, a lucky integer is an integer that has a frequency in the array
 * equal to its value.
 *
 * Return the largest lucky integer in the array. If there is no lucky integer return -1.
 *
 * ! 1 <= arr.length <= 500
 * ! 1 <= arr[i] <= 500
 */

class Solution {
public:
    int findLucky(std::vector<int>& arr)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : arr) {
            map[val]++;
        }
        int result = -1;
        for (const auto& [val, freq] : map) {
            if (val == freq) {
                result = std::max(result, val);
            }
        }
        return result;
    }
};