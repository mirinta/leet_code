#include <algorithm>
#include <vector>

/**
 * A split of an integer array is good if:
 *
 * The array is split into three non-empty contiguous subarrays - named left, mid, right
 * respectively from left to right.
 *
 * The sum of the elements in left is less than or equal to the sum of the elements in mid, and the
 * sum of the elements in mid is less than or equal to the sum of the elements in right.
 *
 * Given nums, an array of non-negative integers, return the number of good ways to split nums. As
 * the number may be too large, return it modulo 109 + 7.
 *
 * ! 3 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^4
 */

class Solution {
public:
    int waysToSplit(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    // two pointers, TC = O(N), SC = O(N)
    int approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> presum(n);
        presum[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            presum[i] = presum[i - 1] + nums[i];
        }
        int result = 0;
        for (int i = 1, j1 = 1, j2 = 1; i <= n - 2; ++i) {
            j1 = std::max(j1, i);
            while (j1 <= n - 2 && presum[j1] < 2 * presum[i - 1]) {
                j1++;
            }
            j2 = std::max(j2, j1);
            while (j2 <= n - 2 && 2 * presum[j2] <= presum[n - 1] + presum[i - 1]) {
                j2++;
            }
            result = (result + j2 - j1) % kMod;
        }
        return result;
    }

    // prefix sum + binary search, TC = O(NlogN), SC = O(N)
    int approach1(const std::vector<int>& nums)
    {
        // 0 X X X i-1 i X X X j j+1 ... n-1
        // |<--left->| |<-mid->| |<-right->|
        // Equation 1: 1 <= i <= j <= n-2
        //
        // let presum[i] = sum of nums[0:i]
        // sum of nums[0:i-1] = presum[i-1]
        // sum of nums[i:j] = presum[j] - presum[i-1]
        // sum of nums[j+1:n-1] = presum[n-1] - presum[j]
        //
        // Equation 2:
        // presum[i-1] <= presum[j] - presum[i-1]
        // => 2*presum[i-1] <= presum[j]
        //
        // Equation 3:
        // presum[j] - presum[i-1] <= presum[n-1] - presum[j]
        // => presum[j] <= (presum[n-1] + presum[i-1])/2
        //
        // Combine Equation 2 and Equation 3:
        // 2*presum[i-1] <= presum[j] <= (presum[n-1]+presum[i-1])/2
        const int n = nums.size();
        std::vector<int> presum(n);
        presum[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            presum[i] = presum[i - 1] + nums[i];
        }
        int result = 0;
        for (int i = 1; i <= n - 2; ++i) {
            auto iter1 = std::lower_bound(presum.begin() + i, std::prev(presum.end()), 2 * presum[i - 1]);
            auto iter2 =
                std::upper_bound(presum.begin() + i, std::prev(presum.end()), (presum[n - 1] + presum[i - 1]) / 2);
            result = (result + std::max<int>(0, iter2 - iter1)) % kMod;
        }
        return result;
    }
};