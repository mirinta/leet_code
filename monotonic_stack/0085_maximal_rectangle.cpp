#include <stack>
#include <vector>

/**
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing
 * only 1's and return its area.
 *
 * ! rows == matrix.length
 * ! cols == matrix[i].length
 * ! 1 <= row, cols <= 200
 * ! matrix[i][j] is '0' or '1'.
 */

class Solution {
public:
    int maximalRectangle(std::vector<std::vector<char>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> ones(n, 0);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                ones[j] = matrix[i][j] == '0' ? 0 : (1 + ones[j]);
            }
            const auto prevSmaller = getPrevSmaller(ones);
            const auto nextSmaller = getNextSmaller(ones);
            for (int j = 0; j < n; ++j) {
                const int area = (nextSmaller[j] - prevSmaller[j] - 1) * ones[j];
                result = std::max(result, area);
            }
        }
        return result;
    }

private:
    std::vector<int> getPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> getNextSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};