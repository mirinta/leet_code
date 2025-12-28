#include <queue>
#include <vector>

/**
 * 给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。
 *
 * ! 你可以假设 k 总是有效的，在输入数组 不为空 的情况下，1 ≤ k ≤ nums.length。
 *
 * ! 本题与LC 239相同。
 */

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
    {
        std::vector<int> result;
        std::deque<int> deque; // monotonic decreasing
        for (int i = 0; i < k; ++i) {
            push(deque, nums[i]);
        }
        result.push_back(deque.front());
        for (int i = k; i < nums.size(); ++i) {
            if (nums[i - k] == deque.front()) {
                deque.pop_front();
            }
            push(deque, nums[i]);
            result.push_back(deque.front());
        }
        return result;
    }

private:
    void push(std::deque<int>& deque, int val)
    {
        while (!deque.empty() && deque.back() < val) {
            deque.pop_back();
        }
        deque.push_back(val);
    }
};
