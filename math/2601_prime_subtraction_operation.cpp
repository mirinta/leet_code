#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of length n.
 *
 * You can perform the following operation as many times as you want:
 *
 * - Pick an index i that you haven’t picked before, and pick a prime p strictly less than nums[i],
 * then subtract p from nums[i].
 *
 * Return true if you can make nums a strictly increasing array using the above operation and false
 * otherwise.
 *
 * A strictly increasing array is an array whose each element is strictly greater than its preceding
 * element.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 * ! nums.length == n
 */

class Solution {
public:
    bool primeSubOperation(std::vector<int>& nums)
    {
        const int max = *std::max_element(nums.begin(), nums.end());
        std::vector<bool> isPrime(max + 1, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (int x = 2; x <= max; ++x) {
            if (!isPrime[x])
                continue;

            for (int y = x * x; y <= max; y += x) {
                isPrime[y] = false;
            }
        }
        int i = 0;
        int val = 1; // nums[i] >= 1
        while (i < nums.size()) {
            const int diff = nums[i] - val;
            if (diff < 0)
                return false;

            if (diff == 0 || isPrime[diff]) {
                val++;
                i++;
            } else {
                val++;
            }
        }
        return true;
    }
};