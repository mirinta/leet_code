#include <algorithm>
#include <vector>

/**
 * You are given an array of integers "nums" and an integer "target".
 *
 * Return the number of non-empty subsequences of "nums" such that the sum of the minimum and
 * maximum element on it is less or equal to target. Since the answer may be too large, return it
 * module 10^9 + 7.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 * ! 1 <= target <= 10^6
 */

class Solution {
public:
    int numSubseq(std::vector<int>& nums, int target)
    {
        static constexpr long long kMod = 1e9 + 7;
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int lo = 0;
        int hi = n - 1;
        long long result = 0;
        while (lo <= hi) {
            if (nums[lo] + nums[hi] > target) {
                hi--;
            } else {
                // fix nums[lo] as the lower bound:
                // nums[lo:hi] is valid
                // nums[lo:hi-1] is valid
                // ...
                // each elements of nums[lo+1:hi] has two choices: pick or not pick
                result = (result + fastPowMod(2, hi - lo, kMod)) % kMod;
                lo++;
            }
        }
        return result;
    }

private:
    long long fastPowMod(long long a, long long b, long long mod)
    {
        long long base = a;
        long long result = 1;
        while (b > 0) {
            if (b & 1) {
                result = result * base % mod;
            }
            base = base * base % mod;
            b >>= 1;
        }
        return result;
    }
};