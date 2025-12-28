#include <vector>

/**
 * You are given an integer array nums and two integers minK and maxK.
 *
 * A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
 *
 * - The minimum value in the subarray is equal to minK.
 *
 * - The maximum value in the subarray is equal to maxK.
 *
 * Return the number of fixed-bound subarrays.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i], minK, maxK <= 10^6
 */

#include <deque>
#include <vector>

class Solution {
public:
    long long countSubarrays(std::vector<int>& nums, int minK, int maxK)
    {
        return approach2(nums, minK, maxK);
    }

private:
    long long approach2(const std::vector<int>& nums, int minK, int maxK)
    {
        const int n = nums.size();
        int lastMin = -1;
        int lastMax = -1;
        int lastInvalid = -1;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < minK || nums[i] > maxK) {
                lastInvalid = i;
                lastMin = -1;
                lastMax = -1;
                continue;
            }
            if (nums[i] == minK) {
                lastMin = i;
            }
            if (nums[i] == maxK) {
                lastMax = i;
            }
            result += std::max(0, std::min(lastMin, lastMax) - lastInvalid);
        }
        return result;
    }

    long long approach1(const std::vector<int>& nums, int minK, int maxK)
    {
        const int n = nums.size();
        std::deque<int> minDq; // front is the index of the min element
        std::deque<int> maxDq; // front is the index of the max element
        long long result = 0;
        for (int left = 0, i = 0; i < n; ++i) {
            if (nums[i] < minK || nums[i] > maxK) {
                minDq.clear();
                maxDq.clear();
                left = i + 1;
                continue;
            }
            while (!minDq.empty() && nums[i] <= nums[minDq.back()]) {
                minDq.pop_back();
            }
            minDq.push_back(i);
            while (!maxDq.empty() && nums[i] >= nums[maxDq.back()]) {
                maxDq.pop_back();
            }
            maxDq.push_back(i);
            if (nums[minDq.front()] == minK && nums[maxDq.front()] == maxK) {
                result += std::min(minDq.front(), maxDq.front()) - left + 1;
            }
        }
        return result;
    }
};
