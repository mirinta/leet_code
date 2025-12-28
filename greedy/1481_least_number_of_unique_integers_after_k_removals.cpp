#include <unordered_map>
#include <vector>

/**
 * Given an array of integers arr and an integer k. Find the least number of unique integers after
 * removing exactly k elements.
 *
 * ! 1 <= arr.length <= 10^5
 * ! 1 <= arr[i] <= 10^9
 * ! 0 <= k <= arr.length
 */

class Solution {
public:
    int findLeastNumOfUniqueInts(std::vector<int>& arr, int k)
    {
        const int n = arr.size();
        std::unordered_map<int, int> map;
        for (const auto& val : arr) {
            map[val]++;
        }
        // count[i] = num of occurrences of frequency i
        std::vector<int> count(n + 1, 0);
        for (const auto& [val, freq] : map) {
            count[freq]++;
        }
        for (int i = 1, remaining = map.size(); i <= n; ++i) {
            const int remove = std::min(k, i * count[i]);
            remaining -= remove / i;
            k -= remove;
            if (k <= 0)
                return remaining;
        }
        return 0;
    }
};