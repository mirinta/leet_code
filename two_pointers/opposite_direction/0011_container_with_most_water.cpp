#include <vector>

/**
 * You are given an integer array height of length n. There are n vertical lines drawn such that the
 * two endpoints of the ith line are (i, 0) and (i, height[i]).
 *
 * Find two lines that together with the x-axis form a container, such that the container contains
 * the most water.
 *
 * Return the maximum amount of water a container can store.
 *
 * Notice that you may not slant the container.
 *
 * ! n == height.length
 * ! 2 <= n <= 10^5
 * ! 0 <= height[i] <= 10^4
 */

class Solution {
public:
    int maxArea(std::vector<int>& height)
    {
        // the amount of water depends on the line with lower height
        int left = 0;
        int right = height.size() - 1;
        int result = 0;
        while (left < right) {
            result = std::max(result, (right - left) * std::min(height[left], height[right]));
            if (height[left] < height[right]) {
                left++;
            } else if (height[left] > height[right]) {
                right--;
            } else {
                left++;
                right--;
            }
        }
        return result;
    }
};