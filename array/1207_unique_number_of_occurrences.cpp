#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * Given an array of integers arr, return true if the number of occurrences of each value in the
 * array is unique or false otherwise.
 *
 * ! 1 <= arr.length <= 1000
 * ! -1000 <= arr[i] <= 1000
 */

class Solution {
public:
    bool uniqueOccurrences(std::vector<int>& arr)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : arr) {
            map[val]++;
        }
        std::unordered_set<int> set;
        for (const auto& [val, freq] : map) {
            if (set.count(freq))
                return false;

            set.insert(freq);
        }
        return true;
    }
};