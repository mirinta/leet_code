#include <set>
#include <vector>

/**
 * Given an array of integers nums and a positive integer k, check whether it is possible to divide
 * this array into sets of k consecutive numbers.
 *
 * Return true if it is possible. Otherwise, return false.
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 *
 * ! This problem is the same as 846.
 */

class Solution {
public:
    bool isPossibleDivide(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        if (n % k)
            return false;

        const int groups = n / k;
        std::multiset<int> set(nums.begin(), nums.end());
        for (int i = 0; i < groups; ++i) {
            const int min = *set.begin();
            for (int val = min; val <= min + k - 1; ++val) {
                auto iter = set.find(val);
                if (iter == set.end())
                    return false;

                set.erase(iter);
            }
        }
        return true;
    }
};