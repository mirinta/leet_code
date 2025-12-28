#include <vector>

/**
 * You are given an integer array pref of size n. Find and return the array arr of size n that
 * satisfies:
 *
 * - pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
 *
 * Note that ^ denotes the bitwise-xor operation.
 *
 * It can be proven that the answer is unique.
 *
 * ! 1 <= pref.length <= 10^5
 * ! 0 <= pref[i] <= 10^6
 */

class Solution {
public:
    std::vector<int> findArray(std::vector<int>& pref)
    {
        const int n = pref.size();
        std::vector<int> result(n);
        result[0] = pref[0];
        for (int i = 1; i < n; ++i) {
            result[i] = pref[i] ^ pref[i - 1];
        }
        return result;
    }
};
