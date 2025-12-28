#include <array>
#include <vector>

/**
 * You are given two integer arrays of equal length target and arr. In one step, you can select any
 * non-empty subarray of arr and reverse it. You are allowed to make any number of steps.
 *
 * Return true if you can make arr equal to target or false otherwise.
 *
 * ! target.length == arr.length
 * ! 1 <= target.length <= 1000
 * ! 1 <= target[i] <= 1000
 * ! 1 <= arr[i] <= 1000
 */

class Solution {
public:
    bool canBeEqual(std::vector<int>& target, std::vector<int>& arr)
    {
        std::array<int, 1001> count{};
        for (const auto& val : target) {
            count[val]++;
        }
        for (const auto& val : arr) {
            if (--count[val] < 0)
                return false;
        }
        for (const auto& freq : count) {
            if (freq != 0)
                return false;
        }
        return true;
    }
};