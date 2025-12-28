#include <vector>

/**
 * 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
 *
 * 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
 *
 * ! 1 <= target <= 10^5
 */

class Solution {
public:
    std::vector<std::vector<int>> findContinuousSequence(int target)
    {
        int start = 1;
        int end = 1;
        int sum = 0;
        std::vector<std::vector<int>> result;
        // sliding window, elements in range [start, end)
        while (start <= target / 2) {
            if (sum < target) {
                sum += end;
                end++;
            } else if (sum > target) {
                sum -= start;
                start++;
            } else {
                std::vector<int> nums;
                for (int i = start; i < end; ++i) {
                    nums.push_back(i);
                }
                result.push_back(std::move(nums));
                sum -= start;
                start++;
            }
        }
        return result;
    }
};