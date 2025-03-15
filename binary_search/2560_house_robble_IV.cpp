#include <algorithm>
#include <vector>

/**
 * There are several consecutive houses along a street, each of which has some money inside. There
 * is also a robber, who wants to steal money from the homes, but he refuses to steal from adjacent
 * homes.
 *
 * The capability of the robber is the maximum amount of money he steals from one house of all the
 * houses he robbed.
 *
 * You are given an integer array nums representing how much money is stashed in each house. More
 * formally, the ith house from the left has nums[i] dollars.
 *
 * You are also given an integer k, representing the minimum number of houses the robber will steal
 * from. It is always possible to steal at least k houses.
 *
 * Return the minimum capability of the robber out of all the possible ways to steal at least k
 * houses.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= (nums.length + 1)/2
 */

class Solution
{
public:
    int minCapability(std::vector<int>& nums, int k)
    {
        int lo = *std::min_element(nums.begin(), nums.end());
        int hi = *std::max_element(nums.begin(), nums.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, k)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int max, const std::vector<int>& nums, int k)
    {
        int count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] <= capacity) {
                count++;
                i++;
            }
            if (count >= k)
                return true;
        }
        return false;
    }
};
