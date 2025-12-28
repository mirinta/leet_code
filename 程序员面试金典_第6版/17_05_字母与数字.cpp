#include <string>
#include <unordered_map>
#include <vector>

/**
 * 给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。
 *
 * 返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。若不存在这样的数组，返回一个空数组。
 *
 * ! array.length <= 100000
 */

class Solution {
public:
    std::vector<std::string> findLongestSubarray(std::vector<std::string>& array)
    {
        // digits[i] = num of digits in array[0:i]
        // if array[j+1:i] is a valid subarray,
        // 2 * num of digits in array[j+1:i] = length of array[j+1:i]
        // 2 * (digits[i] - digits[j]) = i - j
        // 2 * digits[i] - i = 2 * digits[j] - j
        const int n = array.size();
        // base case: array[0:i] is a valid subarray
        // 2 * digits[i] - i = 1, length = i - j = i + 1
        // thus, map[1] = -1
        std::unordered_map<int, int> map;
        map[1] = -1;
        int digits = 0;
        int endIndex = INT_MAX;
        int maxLength = INT_MIN;
        for (int i = 0; i < n; ++i) {
            digits += std::isdigit(array[i][0]);
            const int target = 2 * digits - i;
            if (map.count(target)) {
                const int j = map[target];
                if (i - j > maxLength) {
                    maxLength = i - j;
                    endIndex = i;
                } else if (i - j == maxLength) {
                    endIndex = std::min(endIndex, i);
                }
            } else {
                map[target] = i;
            }
        }
        if (maxLength == INT_MIN)
            return {};

        const int startIndex = endIndex - maxLength + 1;
        return {array.begin() + startIndex, array.begin() + startIndex + maxLength};
    }
};