#include <algorithm>
#include <vector>

/**
 * A sequence of numbers is called arithmetic if it consists of at least two elements, and the
 * difference between every two consecutive elements is the same. More formally, a sequence s is
 * arithmetic if and only if s[i+1] - s[i] == s[1] - s[0] for all valid i.
 *
 * For example, these are arithmetic sequences:
 *
 * - 1, 3, 5, 7, 9
 *
 * - 7, 7, 7, 7
 *
 * - 3, -1, -5, -9
 *
 * The following sequence is not arithmetic:
 *
 * - 1, 1, 2, 5, 7
 *
 * You are given an array of n integers, nums, and two arrays of m integers each, l and r,
 * representing the m range queries, where the ith query is the range [l[i], r[i]]. All the arrays
 * are 0-indexed.
 *
 * Return a list of boolean elements answer, where answer[i] is true if the subarray nums[l[i]],
 * nums[l[i]+1], ... , nums[r[i]] can be rearranged to form an arithmetic sequence, and false
 * otherwise.
 *
 * ! n == nums.length
 * ! m == l.length
 * ! m == r.length
 * ! 2 <= n <= 500
 * ! 1 <= m <= 500
 * ! 0 <= l[i] < r[i] < n
 * ! -10^5 <= nums[i] <= 10^5
 */

class Solution {
public:
    // time O(MNlogN), space O(N)
    std::vector<bool> checkArithmeticSubarrays(std::vector<int>& nums, std::vector<int>& l, std::vector<int>& r)
    {
        std::vector<bool> result(l.size());
        for (int i = 0; i < result.size(); ++i) {
            std::vector<int> subarray(nums.begin() + l[i], nums.begin() + r[i] + 1);
            result[i] = isArithmetic(subarray);
        }
        return result;
    }

private:
    bool isArithmetic(std::vector<int>& nums)
    {
        if (nums.size() < 2)
            return false;

        std::sort(nums.begin(), nums.end());
        const int diff = nums[1] - nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] - nums[i - 1] != diff)
                return false;
        }
        return true;
    }
};