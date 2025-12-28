#include <stack>
#include <vector>

/**
 * Given n non-negative integers representing an elevation map where the width of each bar is 1,
 * compute how much water it can trap after raining.
 *
 * ! n == height.length
 * ! 1 <= n <= 2 * 10^4
 * ! 0 <= height[i] <= 10^5
 */

class Solution {
public:
    int trap(std::vector<int>& height)
    {
        return approach3(height);
    }

private:
    // monotonic stack, TC = O(N), SC = O(N)
    int approach3(const std::vector<int>& height)
    {
        const int n = height.size();
        std::stack<int> stack;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && height[i] >= height[stack.top()]) {
                const int middleH = height[stack.top()];
                stack.pop();
                if (stack.empty())
                    break;

                const int w = i - stack.top() - 1;
                const int h = std::min(height[i], height[stack.top()]) - middleH;
                result += w * h;
            }
            stack.push(i);
        }
        return result;
    }

    // two pointers, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& height)
    {
        const int n = height.size();
        int left = 0;
        int right = n - 1;
        int prefixMax = height[0];
        int suffixMax = height[n - 1];
        int result = 0;
        while (left <= right) {
            prefixMax = std::max(prefixMax, height[left]);
            suffixMax = std::max(suffixMax, height[right]);
            if (prefixMax < suffixMax) {
                result += prefixMax - height[left];
                left++;
            } else {
                result += suffixMax - height[right];
                right--;
            }
        }
        return result;
    }

    // prefix and suffix max, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& height)
    {
        const int n = height.size();
        std::vector<int> prefixMax(n);
        prefixMax[0] = height[0];
        std::vector<int> suffixMax(n);
        suffixMax[n - 1] = height[n - 1];
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = std::max(prefixMax[i - 1], height[i]);
            suffixMax[n - i - 1] = std::max(suffixMax[n - i], height[n - i - 1]);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += std::min(prefixMax[i], suffixMax[i]) - height[i];
        }
        return result;
    }
};