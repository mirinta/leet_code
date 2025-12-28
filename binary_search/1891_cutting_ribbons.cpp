#include <algorithm>
#include <vector>

/**
 * You are given an integer array ribbons, where ribbons[i] represents the length of the ith ribbon,
 * and an integer k. You may cut any of the ribbons into any number of segments of positive integer
 * lengths, or perform no cuts at all.
 *
 * For example, if you have a ribbon of length 4, you can:
 *
 * - Keep the ribbon of length 4,
 *
 * - Cut it into one ribbon of length 3 and one ribbon of length 1,
 *
 * - Cut it into two ribbons of length 2,
 *
 * - Cut it into one ribbon of length 2 and two ribbons of length 1, or
 *
 * - Cut it into four ribbons of length 1.
 *
 * Your task is to determine the maximum length of ribbon, x, that allows you to cut at least k
 * ribbons, each of length x. You can discard any leftover ribbon from the cuts. If it is impossible
 * to cut k ribbons of the same length, return 0.
 *
 * ! 1 <= ribbons.length <= 10^5
 * ! 1 <= ribbons[i] <= 10^5
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    int maxLength(std::vector<int>& ribbons, int k)
    {
        int lo = 0;
        int hi = *std::max_element(ribbons.begin(), ribbons.end());
        while (lo < hi) {
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, ribbons, k)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return hi;
    }

private:
    bool isValid(int x, const std::vector<int>& ribbons, int k)
    {
        int count = 0;
        for (const auto& len : ribbons) {
            count += len / x;
            if (count >= k)
                return true;
        }
        return false;
    }
};
