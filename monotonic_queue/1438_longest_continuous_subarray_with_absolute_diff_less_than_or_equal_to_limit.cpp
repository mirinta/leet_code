#include <queue>
#include <set>
#include <vector>

/**
 * Given an array of integers nums and an integer limit, return the size of the longest non-empty
 * subarray such that the absolute difference between any two elements of this subarray is less than
 * or equal to limit.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= limit <= 10^9
 */

class Solution {
public:
    int longestSubarray(std::vector<int>& nums, int limit)
    {
        return approach2(nums, limit);
    }

private:
    // sliding window + monotonic queue
    int approach2(const std::vector<int>& nums, int limit)
    {
        const int n = nums.size();
        std::deque<int> maxDeque; // non-increasing, front is the index of the max element
        std::deque<int> minDeque; // non-decreasing, front is the index of the min element
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (!maxDeque.empty() && nums[right] > nums[maxDeque.back()]) {
                maxDeque.pop_back();
            }
            maxDeque.push_back(right);
            while (!minDeque.empty() && nums[right] < nums[minDeque.back()]) {
                minDeque.pop_back();
            }
            minDeque.push_back(right);
            while (!maxDeque.empty() && !minDeque.empty() && nums[maxDeque.front()] - nums[minDeque.front()] > limit) {
                if (left == maxDeque.front()) {
                    maxDeque.pop_front();
                }
                if (left == minDeque.front()) {
                    minDeque.pop_front();
                }
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }

    // sliding window + multiset, TC = O(NlogN), SC = O(N)
    int approach1(const std::vector<int>& nums, int limit)
    {
        // if nums[j:i] is a valid subarray,
        // then max-min <= limit
        const int n = nums.size();
        std::multiset<int> set;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            set.insert(nums[right]);
            while (*set.rbegin() - *set.begin() > limit) {
                set.erase(set.find(nums[left]));
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};
