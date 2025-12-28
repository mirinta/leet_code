#include <algorithm>
#include <climits>
#include <cstddef>
#include <queue>
#include <vector>

/**
 * You are given two 0-indexed integer arrays "nums1" and "nums2" of equal length "n" and a positive
 * integer "k". You must choose a subsequence of indices from "nums1" of length "k".
 *
 * For chosen indices i0, i1, ..., ik-1, your score is defined as:
 *
 * - The sum of the selected elements from "nums1" multiplied with the minimum of the selected
 * elements from "nums2".
 *
 * - It can defined simply as: (nums1[i0] + nums1[i1] + ... + nums1[ik-1]) * min(nums2[i0],
 * nums2[i1], ..., nums2[ik-1]).
 *
 * Return the maximum possible score.
 *
 * A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1}
 * by deleting some or no elements.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 0 <= nums1[i], nums2[j] <= 105
 * ! 1 <= k <= n
 */

class Solution {
public:
    long long maxScore(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        // put nums1[i] and nums2[i] together
        const int n = nums1.size();
        std::vector<std::pair<int, int>> pairs(n); // <nums1[i], nums2[i]>
        for (int i = 0; i < n; ++i) {
            pairs[i].first = nums1[i];
            pairs[i].second = nums2[i];
        }
        // sort by nums2 in descending order
        std::sort(pairs.begin(), pairs.end(), [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
        // min heap to maintain top k elements of nums1
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        long long sum = 0;
        long long result = 0;
        for (const auto& [val1, val2] : pairs) {
            sum += val1;
            pq.push(val1);
            if (pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            if (pq.size() == k) {
                result = std::max(result, sum * val2);
            }
        }
        return result;
    }
};
