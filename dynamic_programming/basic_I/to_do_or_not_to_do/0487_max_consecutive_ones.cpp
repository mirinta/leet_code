#include <queue>
#include <vector>

/**
 * Given a binary array "nums", return the maximum number of consecutive 1's in the array if you can
 * flip at most one 0.
 *
 * ! nums[i] is either 0 or 1
 *
 * ! Follow up:
 * What if the input numbers come in one by one as an infinite stream? In other words, you can't
 * store all numbers coming from the stream as it's too large to hold in memory. Could you solve it
 * efficiently?
 */

class Solution {
public:
    int findMaxConsecutiveOnes(const std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // approach 1: queue, time O(n), space O(1)
    int approach1(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        int result = 0;
        int countZero = 0;
        std::queue<int> queue;
        for (const auto& val : nums) {
            queue.push(val);
            if (val == 0) {
                countZero++;
            }
            while (!queue.empty() && countZero > 1) {
                if (queue.front() == 0) {
                    countZero--;
                }
                queue.pop();
            }
            result = std::max<int>(result, queue.size());
        }
        return result;
    }

    // approach 2: sliding window, time O(n), space O(1)
    int approach2(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        int result = 0;
        int countZero = 0;
        int left = 0;
        int right = 0;
        // sliding window, elements in range [left, right)
        while (right < nums.size()) {
            if (nums[right++] == 0) {
                countZero++;
            }
            while (countZero > 1) {
                if (nums[left++] == 0) {
                    countZero--;
                }
            }
            result = std::max(result, right - left);
        }
        return result;
    }

    // approach 3: DP, time O(n), space O(n)
    int approach3(const std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;

        // dp[i][0] = max number of consecutive 1's that ends with the ith coin and there's no
        // flipped coin dp[i][1] = max number of consecutive 1's that ends with the ith coin and
        // there exists a flipped coin
        const auto n = nums.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(2, 0));
        for (int i = 1; i <= n; ++i) {
            if (nums[i - 1] == 1) {
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = dp[i - 1][1] + 1;
            } else {
                dp[i][0] = 0;
                dp[i][1] = dp[i - 1][0] + 1;
            }
        }
        int result = INT_MIN;
        for (const auto& sub : dp) {
            result = std::max({result, sub[0], sub[1]});
        }
        return result;
    }
};
