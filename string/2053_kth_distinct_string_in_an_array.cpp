#include <string>
#include <unordered_map>
#include <vector>

/**
 * A distinct string is a string that is present only once in an array.
 *
 * Given an array of strings arr, and an integer k, return the kth distinct string present in arr.
 * If there are fewer than k distinct strings, return an empty string "".
 *
 * Note that the strings are considered in the order in which they appear in the array.
 *
 * ! 1 <= k <= arr.length <= 1000
 * ! 1 <= arr[i].length <= 5
 * ! arr[i] consists of lowercase English letters.
 */

class Solution {
public:
    std::string kthDistinct(std::vector<std::string>& arr, int k)
    {
        std::unordered_map<std::string, int> map;
        for (const auto& s : arr) {
            map[s]++;
        }
        for (const auto& s : arr) {
            if (map[s] == 1 && --k == 0)
                return s;
        }
        return {};
    }
};