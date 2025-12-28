#include <unordered_map>
#include <vector>

/**
 * You are given two 0-indexed binary arrays nums1 and nums2. Find the widest pair of indices (i, j)
 * such that i <= j and nums1[i] + nums1[i+1] + ... + nums1[j] == nums2[i] + nums2[i+1] + ... +
 * nums2[j].
 *
 * The widest pair of indices is the pair with the largest distance between i and j. The distance
 * between a pair of indices is defined as j - i + 1.
 *
 * Return the distance of the widest pair of indices. If no pair of indices meets the conditions,
 * return 0.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 10^5
 * ! nums1[i] is either 0 or 1.
 * ! nums2[i] is either 0 or 1.
 */

class Solution {
public:
    int widestPairOfIndices(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        // let nums[i] = nums1[i] - nums2[i] and sum[i] = sum of nums[0:i]
        // nums1[i] + ... + nums[j] = nums2[i] + ... + nums[j]
        // => (nums1[i] - nums2[i]) + ... + (nums1[j] - nums2[j]) = 0
        // => sum[i] = sum[j-1]
        const int n = nums1.size(); // nums1 and nums2 have the same length
        // map[sum[i]] = j means sum[i] = sum[j], i.e., nums[j+1:i] is a valid subarray with length
        // i-j
        // base case: sum[i] = 0, nums[0:i] is a valid subarray with length i+1 thus, we can
        // initialize map[0] = -1
        std::unordered_map<int, int> map;
        map[0] = -1;
        int sum = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums1[i] - nums2[i];
            if (map.count(sum)) {
                result = std::max(result, i - map[sum]);
            } else {
                map[sum] = i;
            }
        }
        return result;
    }
};