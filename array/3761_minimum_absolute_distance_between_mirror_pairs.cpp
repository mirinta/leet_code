#include <climits>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A mirror pair is a pair of indices (i, j) such that:
 *
 * 0 <= i < j < nums.length, and
 * reverse(nums[i]) == nums[j], where reverse(x) denotes the integer formed by reversing the digits of x. Leading zeros
 * are omitted after reversing, for example reverse(120) = 21.
 *
 * Return the minimum absolute distance between the indices of any mirror pair. The absolute distance between indices i
 * and j is abs(i - j).
 *
 * If no mirror pair exists, return -1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9​​​​​​​
 */

class Solution {
public:
    int minMirrorPairDistance(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        int result = INT_MAX;
        for (int i = n - 1; i >= 0; --i) {
            const int target = reverse(nums[i]);
            if (map.count(target)) {
                result = std::min(result, map[target] - i);
            }
            map[nums[i]] = i;
        }
        return result == INT_MAX ? -1 : result;
    }

private:
    int reverse(int n)
    {
        while (n % 10 == 0) {
            n /= 10;
        }
        int result = 0;
        while (n) {
            result = result * 10 + n % 10;
            n /= 10;
        }
        return result;
    }
};
