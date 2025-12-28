#include <stack>
#include <vector>

/**
 * A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j]. The
 * width of such a ramp is j - i.
 *
 * Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in
 * nums, return 0.
 *
 * ! 2 <= nums.length <= 5 * 10^4
 * ! 0 <= nums[i] <= 5 * 10^4
 */

class Solution {
public:
    int maxWidthRamp(std::vector<int>& nums)
    {
        return approach3(nums);
    }

private:
    // monotonic stack, TC = O(N), SC = O(N)
    int approach3(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            if (stack.empty() || nums[stack.top()] > nums[i]) {
                stack.push(i);
            }
        }
        int result = 0;
        for (int j = n - 1; j >= 0; --j) {
            while (!stack.empty() && nums[j] >= nums[stack.top()]) {
                result = std::max(result, j - stack.top());
                stack.pop();
            }
        }
        return result;
    }

    // two pointers, TC = O(N), SC = O(N)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> suffixMax(n);
        suffixMax[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffixMax[i] = std::max(suffixMax[i + 1], nums[i]);
        }
        int i = 0;
        int j = 0;
        int result = 0;
        while (j < n) {
            if (suffixMax[j] >= nums[i]) {
                result = std::max(result, j - i);
                j++;
            } else {
                i++;
            }
        }
        return result;
    }

    // strictly decreasing vector + binary search, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::pair<int, int>> decreasing; // value to index
        int result = 0;
        for (int j = 0; j < n; ++j) {
            if (decreasing.empty() || decreasing.back().first > nums[j]) {
                decreasing.emplace_back(nums[j], j);
                continue;
            }
            int lo = 0;
            int hi = decreasing.size() - 1;
            while (lo <= hi) {
                const int mid = lo + (hi - lo) / 2;
                if (decreasing[mid].first > nums[j]) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (lo < decreasing.size()) {
                result = std::max(result, j - decreasing[lo].second);
            }
        }
        return result;
    }
};