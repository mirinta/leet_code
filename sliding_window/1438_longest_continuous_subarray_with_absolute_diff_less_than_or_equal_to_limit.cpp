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
    // sliding window + monotonic queue, TC = O(N), SC = O(N)
    int approach2(const std::vector<int>& nums, int limit)
    {
        const int n = nums.size();
        std::deque<int> increase; // front() is the min element
        std::deque<int> decrease; // front() is the max element
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            while (!decrease.empty() && nums[right] > decrease.back()) {
                decrease.pop_back();
            }
            decrease.push_back(nums[right]);
            while (!increase.empty() && nums[right] < increase.back()) {
                increase.pop_back();
            }
            increase.push_back(nums[right]);
            while (decrease.front() - increase.front() > limit) {
                if (nums[left] == decrease.front()) {
                    decrease.pop_front();
                }
                if (nums[left] == increase.front()) {
                    increase.pop_front();
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
        const int n = nums.size();
        std::multiset<int> set;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            set.insert(nums[right]);
            while (*set.rbegin() - *set.begin() > limit) {
                auto iter = set.find(nums[left]);
                set.erase(iter);
                left++;
            }
            result = std::max(result, right - left + 1);
        }
        return result;
    }
};