#include <numeric>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the
 * sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.
 *
 * Return the array arr.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^9
 */

class Solution {
public:
    std::vector<long long> distance(std::vector<int>& nums)
    {
        // jp ... jq ... i ... jx ... jy, length = N
        // ans[i] = (i - jp) + ... + (i - jq) + (jx - i) + ... + (jy - i)
        // ans[i] = N1 * i - sum of [jp:jq] + sum of [jx:jy] - N2 * i
        // where N1 + N2 + 1 = N,
        // sum of [jp:jq] + sum of [jx:jy] + i = total
        const int n = nums.size();
        std::unordered_map<int, std::vector<long long>> map;
        std::vector<long long> result(n, 0);
        for (int i = 0; i < n; ++i) {
            map[nums[i]].push_back(i);
        }
        for (const auto& [_, v] : map) {
            const long long m = v.size();
            const long long total = std::accumulate(v.begin(), v.end(), 0LL);
            long long sum = 0;
            for (long long i = 0; i < m; ++i) {
                result[v[i]] = v[i] * (2 * i - m) - 2 * sum + total;
                sum += v[i];
            }
        }
        return result;
    }
};