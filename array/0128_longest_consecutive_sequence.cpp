#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>

/**
 * Given an unsorted array of integers nums, return the length of the longest consecutive elements
 * sequence.
 *
 * You must write an algorithm that runs in O(n) time.
 *
 * ! 0 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int longestConsecutive(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    // time O(N), space O(N)
    int approach2(const std::vector<int>& nums)
    {
        std::unordered_set<int> set(nums.begin(), nums.end());
        int result = 0;
        for (const auto& val : nums) {
            // if val-1 is found, it means that val is not the beginning of the consecutive sequence
            if (set.count(val - 1))
                continue;

            int count = 0;
            int current = val;
            while (set.count(current)) {
                set.erase(current);
                current++;
                count++;
            }
            result = std::max(result, count);
        }
        return result;
    }

    // time O(NlogN), space O(N)
    int approach1(const std::vector<int>& nums)
    {
        std::set<int> set(nums.begin(), nums.end());
        auto i = set.begin();
        int result = 0;
        while (i != set.end()) {
            auto j = std::next(i, 1);
            while (j != set.end() && *j - *std::prev(j) == 1) {
                j = std::next(j, 1);
            }
            result = std::max<int>(result, std::distance(i, j));
            i = j;
        }
        return result;
    }
};
