#include <algorithm>
#include <cmath>
#include <vector>

/**
 * You are given an integer array nums of size n where n is even, and an integer k.
 *
 * You can perform some changes on the array, where in one change you can replace any element in the
 * array with any integer in the range from 0 to k.
 *
 * You need to perform some changes (possibly none) such that the final array satisfies the
 * following condition:
 *
 * - There exists an integer X such that abs(a[i] - a[n - i - 1]) = X for all (0 <= i < n).
 *
 * Return the minimum number of changes required to satisfy the above condition.
 *
 * ! 2 <= n == nums.length <= 10^5
 * ! n is even.
 * ! 0 <= nums[i] <= k <= 10^5
 */

class Solution {
public:
    int minChanges(std::vector<int>& nums, int k)
    {
        // given a pair of numbers a and b,
        // let curDiff = |a - b|
        // change only one number:
        // - if we change a, then the max diff we can get is max(|k - b|, b)
        // - if we change b, then the max diff we can get is max(|k - a|, a)
        // let maxDiff = max(k - b, k - a, b, a), because k >= nums[i] is guaranteed
        //
        // if x == curDiff, #changes = 0
        // if x is in [0:maxDiff], #changes = 1
        // if x is in (maxDiff, k], #changes = 2
        const int n = nums.size();
        // changes[i] = total num of changes if X = i, 0 <= i <= k
        // diff[i] = t, means all elements of changes[i:k] += t
        std::vector<int> diff(k + 1);
        for (int i = 0; i < n / 2; ++i) {
            const auto& a = nums[i];
            const auto& b = nums[n - i - 1];
            const int curDiff = std::abs(a - b);
            const int maxDiff = std::max({k - a, k - b, a, b});
            diff[0]++;
            if (maxDiff + 1 < diff.size()) {
                diff[maxDiff + 1]++;
            }
            diff[curDiff]--;
            if (curDiff + 1 < diff.size()) {
                diff[curDiff + 1]++;
            }
        }
        int result = n / 2; // at most n/2 changes
        int changes = 0;
        for (int i = 0; i < diff.size(); ++i) {
            changes += diff[i];
            result = std::min(result, changes);
        }
        return result;
    }
};
