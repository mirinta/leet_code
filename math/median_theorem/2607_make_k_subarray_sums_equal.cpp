#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * You are given a 0-indexed integer array arr and an integer k. The array arr is circular. In other
 * words, the first element of the array is the next element of the last element, and the last
 * element of the array is the previous element of the first element.
 *
 * You can do the following operation any number of times:
 *
 * Pick any element from arr and increase or decrease it by 1.
 * Return the minimum number of operations such that the sum of each subarray of length k is equal.
 *
 * A subarray is a contiguous part of the array.
 *
 * ! 1 <= k <= arr.length <= 10^5
 * ! 1 <= arr[i] <= 10^9
 */

class Solution {
public:
    long long makeSubKSumEqual(std::vector<int>& arr, int k)
    {
        // let sum[0:i] represents the sum of subarray arr[0:i]
        // we want each subarray of length k is equal:
        // - sum[0:k-1] = sum[1:k] => nums[0] = nums[k]
        // - sum[k:2k-1] = sum[k+1:2k] => nums[k] = nums[2k]
        // - it implies that nums[0] = nums[k] = nums[2k] = ...
        // similarly, we have:
        // - nums[1] = nums[1+k] = nums[1+2k] = ...
        // - ...
        // - nums[j] = nums[j+k] = nums[j+2k] = ...
        // all indices can be divided into several groups
        // for each group,
        // we need to find the minimum num of operations to make elements equal
        const int n = arr.size();
        std::unordered_set<int> visited;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            if (visited.size() == n)
                break;

            std::vector<int> nums;
            int j = i;
            while (!visited.count(j)) {
                visited.insert(j);
                nums.push_back(arr[j]);
                j = (j + k) % n; // the given array is circular
            }
            result += minOperationsToMakeElementsEqual(nums);
        }
        return result;
    }

private:
    long long minOperationsToMakeElementsEqual(std::vector<int>& nums)
    {
        // find a number x such that
        // |nums[0]-x| + |nums[1]-x| + ... + |nums[n-1]-x| is minimized
        // x is the median of nums
        std::sort(nums.begin(), nums.end());
        const auto& median = nums[nums.size() / 2];
        long long result = 0;
        for (const auto& val : nums) {
            result += std::abs(val - median);
        }
        return result;
    }
};