#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A special triplet is defined as a triplet of indices (i, j, k) such that:
 *
 * - 0 <= i < j < k < n, where n = nums.length
 *
 * - nums[i] == nums[j] * 2
 *
 * - nums[k] == nums[j] * 2
 *
 * Return the total number of special triplets in the array.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * ! 3 <= n == nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 */

class Solution
{
public:
    int specialTriplets(std::vector<int>& nums)
    {
        static constexpr long long kMod = 1e9 + 7;
        const int n = nums.size();
        std::vector<long long> count(n);
        std::unordered_map<int, long long> map;
        for (int i = 0; i < n; ++i) {
            count[i] = (count[i] + map[2 * nums[i]]) % kMod;
            map[nums[i]]++;
        }
        map.clear();
        for (int i = n - 1; i >= 0; --i) {
            count[i] = count[i] * map[2 * nums[i]] % kMod;
            map[nums[i]]++;
        }
        long long result = 0;
        for (const auto& v : count) {
            result = (result + v) % kMod;
        }
        return result;
    }
};