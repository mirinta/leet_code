#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums. The uniqueness array of nums is the sorted array that
 * contains the number of distinct elements of all the subarrays of nums. In other words, it is a
 * sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
 *
 * Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at
 * index i and ends at index j.
 *
 * Return the median of the uniqueness array of nums.
 *
 * Note that the median of an array is defined as the middle element of the array when it is sorted
 * in non-decreasing order. If there are two choices for a median, the smaller of the two values is
 * taken.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    int medianOfUniquenessArray(std::vector<int>& nums)
    {
        const long long n = nums.size();
        const long long m = n * (n + 1) / 2; // total num of non-empty subarrays
        const long long k = (m + 1) / 2;     // median = kth smallest (1-indexed)
        // find the kth smallest of all distinct(nums[i:j])
        int lo = 1;
        int hi = n;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (helper(mid, k, nums)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    // count the num of subarrays that distinct(arr) <= max,
    // check the count >= k
    long long helper(long long max, long long k, const std::vector<int>& nums)
    {
        const long long n = nums.size();
        std::unordered_map<int, long long> map;
        long long count = 0;
        for (long long left = 0, right = 0; right < n; ++right) {
            map[nums[right]]++;
            while (map.size() > max) {
                if (--map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            count += right - left + 1;
            if (count >= k)
                return true;
        }
        return false;
    }
};