#include <algorithm>
#include <vector>

/**
 * You are given two 1-indexed integer arrays, nums and, changeIndices, having lengths n and m,
 * respectively.
 *
 * Initially, all indices in nums are unmarked. Your task is to mark all indices in nums.
 *
 * In each second, s, in order from 1 to m (inclusive), you can perform one of the following
 * operations:
 *
 * - Choose an index i in the range [1, n] and decrement nums[i] by 1.
 *
 * - If nums[changeIndices[s]] is equal to 0, mark the index changeIndices[s].
 *
 * - Do nothing.
 *
 * Return an integer denoting the earliest second in the range [1, m] when all indices in nums can
 * be marked by choosing operations optimally, or -1 if it is impossible.
 *
 * ! 1 <= n == nums.length <= 2000
 * ! 0 <= nums[i] <= 10^9
 * ! 1 <= m == changeIndices.length <= 2000
 * ! 1 <= changeIndices[i] <= n
 */

class Solution {
public:
    int earliestSecondToMarkIndices(std::vector<int>& nums, std::vector<int>& changeIndices)
    {
        const int m = changeIndices.size();
        int lo = 1;
        int hi = m;
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, changeIndices)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo > m ? -1 : lo;
    }

private:
    // check if changeIndices[1:maxTime] can mark all indices of nums
    bool isValid(int maxTime, const std::vector<int>& nums, const std::vector<int>& changeIndices)
    {
        const int n = nums.size();
        std::vector<int> last(n, -1);
        for (int s = 0; s < maxTime; ++s) {
            last[changeIndices[s] - 1] = s;
        }
        if (std::any_of(last.begin(), last.end(), [](const auto& i) { return i == -1; }))
            return false;

        int count = 0; // num of decrement operations
        for (int s = 0; s < maxTime; ++s) {
            const int i = changeIndices[s] - 1;
            if (last[i] != s) {
                count++;
                continue;
            }
            if (nums[i] > count)
                return false;

            count -= nums[i];
        }
        return true;
    }
};