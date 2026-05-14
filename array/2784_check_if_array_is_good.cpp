#include <vector>

/**
 * You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].
 *
 * base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly
 * once, plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].
 *
 * Return true if the given array is good, otherwise return false.
 *
 * Note: A permutation of integers represents an arrangement of these numbers.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= num[i] <= 200
 */

class Solution {
public:
    bool isGood(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> count(n);
        for (const auto& val : nums) {
            if (val >= n || val <= 0)
                return false;

            if (val == n - 1 && count[val] > 1)
                return false;

            if (val < n - 1 && count[val] > 0)
                return false;

            count[val]++;
        }
        return true;
    }
};
