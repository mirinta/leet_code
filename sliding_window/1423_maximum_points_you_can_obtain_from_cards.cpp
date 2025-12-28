#include <vector>

/**
 * There are several cards arranged in a row, and each card has an associated number of points. The
 * points are given in the integer array cardPoints.
 *
 * In one step, you can take one card from the beginning or from the end of the row. You have to
 * take exactly k cards.
 *
 * Your score is the sum of the points of the cards you have taken.
 *
 * Given the integer array cardPoints and the integer k, return the maximum score you can obtain.
 *
 * ! 1 <= cardPoints.length <= 10^5
 * ! 1 <= cardPoints[i] <= 10^4
 * ! 1 <= k <= cardPoints.length
 */

class Solution {
public:
    int maxScore(std::vector<int>& cardPoints, int k)
    {
        // [0 ... x-1] [x ... y] [y+1 ... n-1]
        // score = sum[0:x-1] + sum[y+1:n-1]
        // since sum[0:x-1] + sum[y+1:n-1] + sum[x:y] = total
        // then score = total - sum[x:y]
        // maximize score is equivalent to minimize sum[x:y]
        // length of nums[x:y] = L - k
        const int n = cardPoints.size();
        int sum = 0;
        int min = INT_MAX;
        int total = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += cardPoints[right];
            total += cardPoints[right];
            if (right - left + 1 > n - k) {
                sum -= cardPoints[left];
                left++;
            }
            if (right - left + 1 == n - k) {
                min = std::min(min, sum);
            }
        }
        return total - min;
    }
};