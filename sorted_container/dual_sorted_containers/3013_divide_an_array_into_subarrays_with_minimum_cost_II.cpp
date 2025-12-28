#include <set>
#include <vector>

/**
 * You are given a 0-indexed array of integers nums of length n, and two positive integers k and
 * dist.
 *
 * The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1
 * while the cost of [3,4,1] is 3.
 *
 * You need to divide nums into k disjoint contiguous subarrays , such that the difference between
 * the starting index of the second subarray and the starting index of the kth subarray should be
 * less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 -
 * 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.
 *
 * Return the minimum possible sum of the cost of these subarrays.
 *
 * ! 3 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 3 <= k <= n
 * ! k - 2 <= dist <= n - 2
 */

class Solution {
public:
    long long minimumCost(std::vector<int>& nums, int k, int dist)
    {
        // LC 3010 asks us to partition nums into 3 disjoint subarrays
        // and the answer = nums[0] + sum of the top 2 smallest elements in nums[1:n)
        // In this problem:
        // - Assume i is the starting index of the second subarray,
        //   and j is the starting index of the last subarray.
        // - We want j-i <= dist which is equivalent to j-i+1 <= dist+1.
        // - Consider a sliding window [i:j],
        //   we need to find the sum of the top k-1 smallest elements in nums[i:j]
        //   and the window size = j-i+1 <= dist+1.
        // - As the number of elements in the sliding window increases,
        //   the likelihood of identifying smaller elements also rises.
        //   Thus, we fix the sliding window size as dist+1.
        const int n = nums.size();
        const int targetNum = k - 1;
        const int windowSize = dist + 1;
        std::multiset<int> set1;      // the top targetNum smallest elements of the sliding window
        std::multiset<int> set2;      // the remaining elements of the sliding window
        long long sum = 0;            // sum of the top targetNum smallest elements of the sliding window
        long long result = LLONG_MAX; // final result = nums[0] + min sum
        for (int i = 1; i < n; ++i) {
            if (set1.size() < targetNum) {
                sum += nums[i];
                set1.insert(nums[i]);
            } else if (nums[i] >= *set1.rbegin()) {
                set2.insert(nums[i]);
            } else {
                set2.insert(*set1.rbegin());
                sum -= *set1.rbegin();
                set1.erase(std::prev(set1.end()));
                set1.insert(nums[i]);
                sum += nums[i];
            }
            if (i > windowSize) { // #NOTE# we start from index 1
                const int out = nums[i - windowSize];
                if (auto iter = set2.find(out); iter != set2.end()) {
                    set2.erase(iter);
                } else {
                    sum -= out;
                    set1.erase(set1.find(out));
                    if (!set2.empty()) {
                        set1.insert(*set2.begin());
                        sum += *set2.begin();
                        set2.erase(set2.begin());
                    }
                }
            }
            if (set1.size() == targetNum) {
                result = std::min(result, sum + nums[0]);
            }
        }
        return result;
    }
};