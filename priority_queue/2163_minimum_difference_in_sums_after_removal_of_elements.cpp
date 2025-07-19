#include <queue>
#include <vector>

/**
 * You are given a 0-indexed integer array nums consisting of 3 * n elements.
 *
 * You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining
 * 2 * n elements will be divided into two equal parts:
 *
 * - The first n elements belonging to the first part and their sum is sumfirst.
 *
 * - The next n elements belonging to the second part and their sum is sumsecond.
 *
 * The difference in sums of the two parts is denoted as sumfirst - sumsecond.
 *
 * - For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
 *
 * - Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
 *
 * Return the minimum difference possible between the sums of the two parts after the removal of n
 * elements.
 *
 * ! nums.length == 3 * n
 * ! 1 <= n <= 10^5
 * ! 1 <= nums[i] <= 10^5
 */

class Solution
{
public:
    long long minimumDifference(std::vector<int>& nums)
    {
        const int m = nums.size();
        const int n = m / 3;
        // left[i] = min sum of top n smallest elements of nums[0:i]
        std::vector<long long> left(m, LLONG_MAX);
        std::priority_queue<long long> maxHeap;
        // right[i] = max sum of top n largest elements of nums[i:n-1]
        std::vector<long long> right(m, LLONG_MIN);
        std::priority_queue<long long, std::vector<long long>, std::greater<>> minHeap;
        for (long long i = 0, sumLeft = 0, sumRight = 0; i < m; ++i) {
            sumLeft += nums[i];
            maxHeap.emplace(nums[i]);
            if (maxHeap.size() > n) {
                sumLeft -= maxHeap.top();
                maxHeap.pop();
            }
            if (maxHeap.size() == n) {
                left[i] = sumLeft;
            }
            sumRight += nums[m - i - 1];
            minHeap.emplace(nums[m - i - 1]);
            if (minHeap.size() > n) {
                sumRight -= minHeap.top();
                minHeap.pop();
            }
            if (minHeap.size() == n) {
                right[m - i - 1] = sumRight;
            }
        }
        long long result = LLONG_MAX;
        for (long long i = n - 1; i < m - n; ++i) {
            result = std::min(result, left[i] - right[i + 1]);
        }
        return result;
    }
};