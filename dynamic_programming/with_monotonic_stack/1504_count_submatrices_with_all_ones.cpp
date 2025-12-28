#include <stack>
#include <vector>

/**
 * Given an m x n binary matrix mat, return the number of submatrices that have all ones.
 *
 * ! 1 <= m, n <= 150
 * ! mat[i][j] is either 0 or 1.
 */

class Solution {
public:
    int numSubmat(std::vector<std::vector<int>>& mat)
    {
        return approach2(mat);
    }

private:
    // Monotonic stack, TC = O(MN), SC = O(N)
    int approach2(const std::vector<std::vector<int>>& mat)
    {
        // fix the ith row as bottom border
        const int m = mat.size();
        const int n = mat[0].size();
        std::vector<int> height(n, 0);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                height[j] = mat[i][j] == 0 ? 0 : (height[j] + 1);
            }
            result += helper(height);
        }
        return result;
    }

    int helper(const std::vector<int>& height)
    {
        // height[i] = height of bar[i]
        // dp[i] = num of rectangles in bar[0:i] whose right border is bar[i]
        // case 1: height[i] >= height[i-1]
        // - all rectangles of dp[i-1] can extend their right border to bar[i]
        // - bar[i] itself contains height[i] rectangles
        // - thus, dp[i] = dp[i-1] + height[i]
        // case 2: find the largest j such that height[j] <= height[i]
        // - all rectangles of dp[j] can extend their right border to bar[i]
        // - height[j+1:i-1] > height[i],
        //   heights of rectangles in bar[j+1:i] can be [1,height[i]]
        //   widths of rectangles in bar[j+1:i] can be [1,i-j]
        // - thus, dp[i] = dp[j] + height[i] * (i-j)
        // case 3: j doesn't exist, then heights[0:i-1] > height[i]
        // - dp[i] = 0 + height[i] * (i+1)
        const int n = height.size();
        std::vector<int> dp(n, 0);
        dp[0] = height[0];
        const auto prevSmallerOrEqual = getPrevSmallerOrEqual(height);
        int total = dp[0];
        for (int i = 1; i < n; ++i) {
            const int j = prevSmallerOrEqual[i];
            if (j >= 0) {
                dp[i] += dp[j];
            }
            dp[i] += height[i] * (i - j);
            total += dp[i];
        }
        return total;
    }

    std::vector<int> getPrevSmallerOrEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n, -1);
        std::stack<int> stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[stack.top()] > nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    // Enumeration, TC = O(MNN), SC = O(N)
    int approach1(const std::vector<std::vector<int>>& mat)
    {
        // given a fixed bottom border, how many rectangles are there in the following diagram?
        // - choose bar0 as the left border and bar0 as the right border
        //   width = 1 and height = 1, count = 1
        // - choose bar1 as the left border and bar1 as the right border
        //   width = 1 and height = {1,2}, count = 1x2 = 2
        // - choose bar0 as the left border and bar1 as the right border
        //   width = 2 and height = 1 = min height of bar0 and bar1, count = 1
        // - total num of rectangles = 1+2+1=4
        //
        //            height=2
        //            +-----+
        //   height=1 |     |
        //   +-----+  +-----+
        //   |     |  |     |
        // --+-----+--+-----+-- bottom border
        //     bar0     bar1
        //
        // in general:
        // fix the ith row as the bottom border
        // let heights[j] = num of consecutive ones from mat[i][j] to mat[0][j]
        // for each pair of j and k (j <= k):
        // let heights[j] and heights[k] be the left and right border
        // num of rectangles = min of heights[j],heights[j+1],...,heights[k]
        const int m = mat.size();
        const int n = mat[0].size();
        std::vector<int> height(n, 0);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                height[j] = mat[i][j] == 1 ? 1 + height[j] : 0;
            }
            for (int j = 0; j < n; ++j) {
                int min = height[j];
                for (int k = j; k < n; ++k) {
                    min = std::min(min, height[k]);
                    result += min;
                }
            }
        }
        return result;
    }
};