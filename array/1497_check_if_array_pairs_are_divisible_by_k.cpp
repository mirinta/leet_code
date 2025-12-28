#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr of even length n and an integer k.
 *
 * We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible
 * by k.
 *
 * Return true If you can find a way to do that or false otherwise.
 *
 * ! arr.length == n
 * ! 1 <= n <= 10^5
 * ! n is even.
 * ! -10^9 <= arr[i] <= 10^9
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    bool canArrange(std::vector<int>& arr, int k)
    {
        std::unordered_map<int, int> map; // remainder to count
        for (const auto& val : arr) {
            map[(val % k + k) % k]++; // prevent negative values
        }
        if (map.count(0) && map[0] % 2)
            return false;

        for (const auto& [remainder, count] : map) {
            if (remainder == 0)
                continue;

            if (!map.count(k - remainder) || count != map[k - remainder])
                return false;
        }
        return true;
    }
};