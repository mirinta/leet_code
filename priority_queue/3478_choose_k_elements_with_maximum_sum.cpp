#include <queue>
#include <vector>

/**
 * You are given two integer arrays, nums1 and nums2, both of length n, along with a positive
 * integer k.
 *
 * For each index i from 0 to n - 1, perform the following:
 *
 * - Find all indices j where nums1[j] is less than nums1[i].
 *
 * - Choose at most k values of nums2[j] at these indices to maximize the total sum.
 *
 * Return an array answer of size n, where answer[i] represents the result for the corresponding
 * index i.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! 1 <= nums1[i], nums2[i] <= 10^6
 * ! 1 <= k <= n
 */

class Solution
{
public:
    std::vector<long long> findMaxSum(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        const int n = nums1.size();
        std::vector<std::pair<long long, int>> data;
        data.reserve(n);
        for (int i = 0; i < n; ++i) {
            data.emplace_back(nums1[i], i);
        }
        std::sort(data.begin(), data.end(),
                  [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
        long long sum = 0;
        std::vector<long long> result(n, 0);
        for (int i = 0, j = 0; i < n; ++i) {
            while (data[j].first < data[i].first) {
                sum += nums2[data[j].second];
                pq.push(nums2[data[j].second]);
                j++;
            }
            while (pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            result[data[i].second] = sum;
        }
        return result;
    }
};
