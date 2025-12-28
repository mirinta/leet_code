#include <algorithm>
#include <numeric>
#include <vector>

/**
 * You are given an integer array coins representing coins of different denominations and an integer
 * k.
 *
 * You have an infinite number of coins of each denomination. However, you are not allowed to
 * combine coins of different denominations.
 *
 * Return the kth smallest amount that can be made using these coins.
 *
 * ! 1 <= coins.length <= 15
 * ! 1 <= coins[i] <= 25
 * ! 1 <= k <= 2 * 10^9
 * ! coins contains pairwise distinct integers.
 */

class Solution {
public:
    long long findKthSmallest(std::vector<int>& coins, int k)
    {
        long long lo = *std::min_element(coins.begin(), coins.end());
        long long hi = static_cast<long long>(*std::max_element(coins.begin(), coins.end())) * k;
        while (lo < hi) {
            const long long mid = lo + (hi - lo) / 2;
            if (isValid(mid, coins, k)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    // check if the num of elements of nums that are <= max is >= k
    bool isValid(long long max, const std::vector<int>& nums, int k)
    {
        long long count = 0;
        const int n = nums.size();
        for (int mask = 1; mask < (1 << n); ++mask) {
            int lcm = 1;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    lcm = std::lcm(nums[i], lcm);
                }
            }
            count += (numOfBinaryOnes(mask) % 2 ? 1 : -1) * max / lcm;
        }
        return count >= k;
    }

    int numOfBinaryOnes(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};