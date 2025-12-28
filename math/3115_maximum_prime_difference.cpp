#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * Return an integer that is the maximum distance between the indices of two (not necessarily
 * different) prime numbers in nums.
 *
 * ! 1 <= nums.length <= 3 * 10^5
 * ! 1 <= nums[i] <= 100
 * ! The input is generated such that the number of prime numbers in the nums is at least one.
 */

class Solution {
public:
    int maximumPrimeDifference(std::vector<int>& nums)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        std::vector<bool> isPrime(max + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (long long i = 2; i <= max; ++i) {
            if (!isPrime[i])
                continue;

            for (long long j = i * i; j <= max; j += i) {
                isPrime[j] = false;
            }
        }
        int earliest = INT_MAX;
        int latest = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            if (isPrime[nums[i]]) {
                earliest = std::min(earliest, i);
                latest = std::max(latest, i);
            }
        }
        return latest - earliest;
    }
};