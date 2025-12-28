#include <vector>

/**
 * You are given a 0-indexed binary array nums of length n, a positive integer k and a non-negative
 * integer maxChanges.
 *
 * Dylan Smith plays a game, where the goal is for Dylan to pick up k ones from nums using the
 * minimum number of moves. When the game starts, Dylan picks up any index dylanIndex in the range
 * [0, n - 1] and stands there. If nums[dylanIndex] == 1 , Dylan picks up the one and
 * nums[dylanIndex] becomes 0 (this does not count as a move). After this, Dylan can make any number
 * of moves (including zero) where in each move Dylan must perform exactly one of the following
 * actions:
 *
 * - Select any index j != dylanIndex such that nums[j] == 0 and set nums[j] = 1. This action can be
 * performed at most maxChanges times.
 *
 * - Select any two adjacent indices x and y (|x - y| == 1) such that nums[x] == 1, nums[y] == 0,
 * then swap their values (set nums[y] = 1 and nums[x] = 0). If y == dylanIndex, Dylan picks up the
 * one after this move and nums[y] becomes 0.
 *
 * Return the minimum number of moves required by Dylan to pick exactly k ones.
 *
 * ! 2 <= n <= 10^5
 * ! 0 <= nums[i] <= 1
 * ! 1 <= k <= 10^5
 * ! 0 <= maxChanges <= 10^5
 * ! maxChanges + sum(nums) >= k
 */

class Solution {
public:
    long long minimumMoves(std::vector<int>& nums, int k, int maxChanges)
    {
        const int n = nums.size();
        int maxConsecutiveOnes = 0; // consider nums[i,i+1,i+2], at most 3
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 0)
                continue;

            int count = 1;
            if (i + 1 < n && nums[i + 1] == 1) {
                count++;
                if (i + 2 < n && nums[i + 2] == 1) {
                    count++;
                }
            }
            maxConsecutiveOnes = std::max(maxConsecutiveOnes, count);
        }
        maxConsecutiveOnes = std::min(maxConsecutiveOnes, k);
        if (k - maxConsecutiveOnes <= maxChanges)
            return std::max(0, maxConsecutiveOnes - 1) + 2 * (k - maxConsecutiveOnes);

        std::vector<int> positions;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                positions.push_back(i);
            }
        }
        const int m = positions.size();
        std::vector<long long> presum(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i - 1] + positions[i - 1];
        }
        const int target = k - maxChanges;
        long long result = LLONG_MAX;
        for (int lo = 0; lo <= positions.size() - target; ++lo) {
            result = std::min(result, 2 * maxChanges + calcOperations(lo, lo + target - 1, presum));
        }
        return result;
    }

private:
    long long calcOperations(int lo, int hi, const std::vector<long long>& presum)
    {
        const int mid = lo + (hi - lo) / 2;
        const long long median = presum[mid + 1] - presum[mid];
        const long long area1 = (mid - lo) * median - (presum[mid] - presum[lo]);
        const long long area2 = (presum[hi + 1] - presum[mid]) - (hi - mid + 1) * median;
        return area1 + area2;
    }
};