#include <unordered_set>
#include <vector>

/**
 * Given an array "arr" of integers, check if there exist two indices i and j such that:
 *
 * - i != j
 *
 * - 0 <= i, j < arr.length
 *
 * - arr[i] == arr[j] * 2
 */

class Solution {
public:
    bool checkIfExist(std::vector<int>& arr)
    {
        std::unordered_set<int> set;
        for (const auto& val : arr) {
            if (set.count(2 * val))
                return true;

            if (val % 2 == 0 && set.count(val / 2))
                return true;

            set.insert(val);
        }
        return false;
    }
};