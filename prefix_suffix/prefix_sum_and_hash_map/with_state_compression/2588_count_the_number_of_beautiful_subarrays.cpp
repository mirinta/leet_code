#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. In one operation, you can:
 *
 * Choose two different indices i and j such that 0 <= i, j < nums.length.
 * Choose a non-negative integer k such that the kth bit (0-indexed) in the binary representation of
 * nums[i] and nums[j] is 1. Subtract 2k from nums[i] and nums[j]. A subarray is beautiful if it is
 * possible to make all of its elements equal to 0 after applying the above operation any number of
 * times.
 *
 * Return the number of beautiful subarrays in the array nums.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^6
 */

class Solution {
public:
    long long beautifulSubarrays(std::vector<int>& nums)
    {
        // if all elements nums[j+1:i] can be changed to 0,
        // then for each bit of the elements, the num of 1's must be even
        // define state:
        // - state[i] = 0 if num of 1's of the ith bit of nums[0:i] is even
        // - state[i] = 1 if num of 1's of the ith bit of nums[0:i] is odd
        // if nums[j+1:i] is a valid subarray,
        // - if state[i] is even, then state[j+1] must be even
        // - if state[i] is odd, then state[j+1] must be odd
        const int n = nums.size();
        std::unordered_map<int, long long> map;
        map[0] = 1;
        int state = 0;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            state ^= nums[i];
            if (map.count(state)) {
                result += map[state];
            }
            map[state]++;
        }
        return result;
    }
};