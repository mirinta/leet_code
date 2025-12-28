#include <stack>
#include <vector>

/**
 * Given an array of integers heights representing the histogram's bar height where the width of
 * each bar is 1, return the area of the largest rectangle in the histogram.
 *
 * ! 1 <= heights.length <= 10^5
 * ! 0 <= heights[i] <= 10^4
 */

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights)
    {
        // Given heights[i], find index j and index k,
        // s.t. heights[j] is the previous smaller element of heights[i],
        // and heights[k] is the next smaller element of heights[i].
        // Then, any index x in the range [j+1,k-1] satisfies heights[x] >= heights[i]
        //    |   |
        //    | | |
        //  | | | | |
        //  j   i   k
        // Then, the max rectangle area of heights[i]=heights[i]*(k-1-(j+1)+1)=heights[i]*(k-j-1)
        // - if j doesn't exist, let j = -1
        // - if k doesn't exist, let k = n
        const int n = heights.size();
        const auto nextSmaller = calcNextSmaller(heights);
        const auto prevSmaller = calcPrevSmaller(heights);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int j = prevSmaller[i];
            const int k = nextSmaller[i];
            result = std::max(result, heights[i] * (k - j - 1));
        }
        return result;
    }

private:
    std::vector<int> calcNextSmaller(const std::vector<int>& heights)
    {
        const int n = heights.size();
        std::stack<std::pair<int, int>> stack; // <val, index>
        std::vector<int> result(n, n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && stack.top().first >= heights[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top().second;
            stack.emplace(heights[i], i);
        }
        return result;
    }

    std::vector<int> calcPrevSmaller(const std::vector<int>& heights)
    {
        const int n = heights.size();
        std::stack<std::pair<int, int>> stack;
        std::vector<int> result(n, -1);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && stack.top().first >= heights[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top().second;
            stack.emplace(heights[i], i);
        }
        return result;
    }
};
