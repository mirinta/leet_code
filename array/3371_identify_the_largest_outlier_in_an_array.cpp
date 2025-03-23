#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums. This array contains n elements, where exactly n - 2 elements
 * are special numbers. One of the remaining two elements is the sum of these special numbers, and
 * the other is an outlier.
 *
 * An outlier is defined as a number that is neither one of the original special numbers nor the
 * element representing the sum of those numbers.
 *
 * Note that special numbers, the sum element, and the outlier must have distinct indices, but may
 * share the same value.
 *
 * Return the largest potential outlier in nums.
 *
 * ! 3 <= nums.length <= 10^5
 * ! -1000 <= nums[i] <= 1000
 * ! The input is generated such that at least one potential outlier exists in nums.
 */

class Solution
{
public:
    int getLargestOutlier(std::vector<int>& nums)
    {
        const int n = nums.size();
        int total = 0;
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            total += val;
            map[val]++;
        }
        int result = INT_MIN;
        for (int i = 0; i < n; ++i) {
            // let nums[i] be the sum element
            // 0 ... ... i-1 i i+1 ... ... n-1
            // |<---left-->|   |<---right--->|
            const int outlier = total - 2 * nums[i];
            if (!map.count(outlier) || (nums[i] == outlier && map[outlier] == 1))
                continue;

            result = std::max(result, outlier);
        }
        return result;
    }
};