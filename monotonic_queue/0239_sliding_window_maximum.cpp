#include <deque>
#include <vector>

/**
 * You are given an array of integers "nums", there is a sliding window of size "k" which is moving
 * from the very left of the array to the very right. You can only see the "k" numbers in the
 * window. Each time the sliding window moves right by one position.
 *
 * Return the max sliding window.
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^4 <= nums[i] <= 10^4
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::deque<int> dq;
        std::vector<int> result;
        result.reserve(n - k + 1);
        for (int i = 0; i < n; ++i) {
            while (!dq.empty() && dq.front() < i - k + 1) {
                dq.pop_front();
            }
            while (!dq.empty() && nums[i] > nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
};
