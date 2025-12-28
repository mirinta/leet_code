#include <algorithm>
#include <vector>

/**
 * There is a grid with n + 2 horizontal bars and m + 2 vertical bars, and initially containing 1 x
 * 1 unit cells.
 *
 * The bars are 1-indexed.
 *
 * You are given the two integers, n and m.
 *
 * You are also given two integer arrays: hBars and vBars.
 *
 * - hBars contains distinct horizontal bars in the range [2, n + 1].
 *
 * - vBars contains distinct vertical bars in the range [2, m + 1].
 *
 * You are allowed to remove bars that satisfy any of the following conditions:
 *
 * - If it is a horizontal bar, it must correspond to a value in hBars.
 *
 * - If it is a vertical bar, it must correspond to a value in vBars.
 *
 * Return an integer denoting the maximum area of a square-shaped hole in the grid after removing
 * some bars (possibly none).
 *
 * ! 1 <= n <= 109
 * ! 1 <= m <= 109
 * ! 1 <= hBars.length <= 100
 * ! 2 <= hBars[i] <= n + 1
 * ! 1 <= vBars.length <= 100
 * ! 2 <= vBars[i] <= m + 1
 * ! All values in hBars are distinct.
 * ! All values in vBars are distinct.
 */

class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, std::vector<int>& hBars, std::vector<int>& vBars)
    {
        // max width and max height can be found separately
        // assume we have bars 1-6 and we can remove {2,3,5}:
        // 1 [2] [3] 4 [5] 6
        // the problem is to find L = the max length of consecutive subarray
        // then max width or max height = L + 1
        const int size = 1 + std::min(maxConsecutiveLength(hBars), maxConsecutiveLength(vBars));
        return size * size;
    }

private:
    int maxConsecutiveLength(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = 0;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && nums[j] - nums[j - 1] == 1) {
                j++;
            }
            result = std::max(result, j - i);
            i = j;
        }
        return result;
    }
};