#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed array nums consisting of positive integers.
 *
 * A partition of an array into one or more contiguous subarrays is called good if no two subarrays
 * contain the same number.
 *
 * Return the total number of good partitions of nums.
 *
 * Since the answer may be large, return it modulo 10^9 + 7.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int numberOfGoodPartitions(std::vector<int>& nums)
    {
        // let nums[i] = nums[j] = x
        // such that i is the first appearance of x and j the last appearance of x
        // then we can't partition nums[i:j]

        // let nums[p] = nums[q] = y
        // i ...... j
        //     p ...... q
        // if p <= j, then we can't partition nums[i:j] and nums[p:q], i.e., nums[i:q]
        // this is similar to merging intervals

        // after merging, assume we have N merged intervals
        // then final answer = 2^(N-1)
        // e.g., partition [1,2,3,4]
        // 1_2_3_4
        //  ^ ^ ^
        // we have 3 positions to "cut" the array, each position has two options: select or not
        // select
        const int n = nums.size();
        std::unordered_map<int, std::pair<int, int>> map;
        for (int i = 0; i < n; ++i) {
            if (!map.count(nums[i])) {
                map[nums[i]] = {i, i};
            } else {
                map[nums[i]].second = i;
            }
        }
        std::vector<std::pair<int, int>> intervals;
        intervals.reserve(map.size());
        for (const auto& pair : map) {
            intervals.push_back(pair.second);
        }
        const int N = mergeIntervals(intervals).size();
        return powmod(2, N - 1, 1e9 + 7);
    }

private:
    std::vector<std::pair<int, int>> mergeIntervals(std::vector<std::pair<int, int>>& intervals)
    {
        std::sort(intervals.begin(), intervals.end());
        std::vector<std::pair<int, int>> merged;
        for (const auto& [start, end] : intervals) {
            if (!merged.empty() && start <= merged.back().second) {
                merged.back().second = std::max(end, merged.back().second);
            } else {
                merged.emplace_back(start, end);
            }
        }
        return merged;
    }

    long long powmod(long long a, long long b, long long mod)
    {
        long long result = 1;
        long long base = a % mod;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};