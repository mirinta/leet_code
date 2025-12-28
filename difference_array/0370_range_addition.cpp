#include <vector>

/**
 * You are given an integer length and an array updates where updates[i] = [startIdxi, endIdxi,
 * inci].
 *
 * You have an array arr of length length with all zeros, and you have some operation to apply on
 * arr. In the ith operation, you should increment all the elements arr[startIdxi], arr[startIdxi +
 * 1], ..., arr[endIdxi] by inci.
 *
 * Return arr after applying all the updates.
 *
 * ! 1 <= length <= 10^5
 * ! 0 <= updates.length <= 10^4
 * ! 0 <= startIdxi <= endIdxi < length
 * ! -1000 <= inci <= 1000
 */

class Solution {
public:
    std::vector<int> getModifiedArray(int length, std::vector<std::vector<int>>& updates)
    {
        // diff[i] = answer[i] - answer[i-1], diff[0] = answer[0]
        std::vector<int> diff(length, 0);
        for (const auto& update : updates) {
            const int lo = update[0];
            const int hi = update[1];
            const int delta = update[2];
            diff[lo] += delta;
            if (hi + 1 < length) {
                diff[hi + 1] -= delta;
            }
        }
        for (int i = 1; i < length; ++i) {
            diff[i] += diff[i - 1];
        }
        return diff;
    }
};