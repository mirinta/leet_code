#include <vector>

/**
 * You are given an integer array, nums, and an integer k. nums comprises of only 0's and 1's. In
 * one move, you can choose two adjacent indices and swap their values.
 *
 * Return the minimum number of moves required so that nums has k consecutive 1's.
 *
 * ! 1 <= nums.length <= 105
 * ! nums[i] is 0 or 1.
 * ! 1 <= k <= sum(nums)
 */

class Solution {
public:
    int minMoves(std::vector<int>& nums, int k)
    {
        std::vector<int> indices; // nums[i] = 1
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 1) {
                indices.push_back(i);
            }
        }
        std::vector<long long> presum(indices.size() + 1, 0);
        for (int i = 1; i <= indices.size(); ++i) {
            presum[i] = presum[i - 1] + indices[i - 1];
        }
        int result = INT_MAX;
        for (int i = 0; i + k - 1 < indices.size(); ++i) {
            // get k 1's and use minimum operations to move them to the same position
            // the extra moves can be removed later
            result = std::min(result, minOperationsToMakeElementsEqual(i, k, presum, indices));
        }
        int offset = 0;
        for (int i = 0; i < k; ++i) {
            offset += std::abs(i - k / 2);
        }
        return result - offset;
    }

private:
    int minOperationsToMakeElementsEqual(int left,
                                         int length,
                                         const std::vector<long long>& presum,
                                         std::vector<int>& nums)
    {
        const int right = left + length - 1;
        const int mid = left + length / 2;
        const long long median = nums[mid];
        const long long area1 = median * (mid - left) - (presum[mid] - presum[left]);
        const long long area2 = (presum[right + 1] - presum[mid]) - median * (right - mid + 1);
        return area1 + area2;
    }
};