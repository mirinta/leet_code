#include <deque>
#include <set>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
 *
 * Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2
 * <= j, 0 <= |nums[i1] - nums[i2]| <= 2. Return the total number of continuous subarrays.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long continuousSubarrays(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // sliding window + monotonic queue, TC = O(N), SC = O(N)
    long long approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::deque<long long> decreasing; // front is the max
        std::deque<long long> increasing; // front is the min
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (!decreasing.empty() && nums[right] > decreasing.back()) {
                decreasing.pop_back();
            }
            decreasing.push_back(nums[right]);
            while (!increasing.empty() && nums[right] < increasing.back()) {
                increasing.pop_back();
            }
            increasing.push_back(nums[right]);
            while (!increasing.empty() && !decreasing.empty() && decreasing.front() - increasing.front() > 2) {
                if (nums[left] == decreasing.front()) {
                    decreasing.pop_front();
                }
                if (nums[left] == increasing.front()) {
                    increasing.pop_front();
                }
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }

    // sliding window + multiset, TC = O(NlogN), SC = O(N)
    long long approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::multiset<int> set;
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            set.insert(nums[right]);
            while (*set.rbegin() - *set.begin() > 2) {
                set.erase(set.find(nums[left]));
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};