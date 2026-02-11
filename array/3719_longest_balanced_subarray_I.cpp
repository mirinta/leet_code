#include <unordered_set>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of
 * distinct odd numbers.
 *
 * Return the length of the longest balanced subarray.
 *
 * ! 1 <= nums.length <= 1500
 * ! 1 <= nums[i] <= 10^5
 */

class Solution {
public:
    int longestBalanced(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_set<int> set;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            set.clear();
            for (int j = i, odd = 0; j < n; ++j) {
                if (set.insert(nums[j]).second) {
                    odd += nums[j] & 1;
                }
                if (odd * 2 == set.size()) {
                    result = std::max(result, j - i + 1);
                }
            }
        }
        return result;
    }
};
