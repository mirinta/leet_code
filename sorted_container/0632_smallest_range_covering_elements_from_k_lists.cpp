#include <set>
#include <tuple>
#include <vector>

/**
 * You have k lists of sorted integers in non-decreasing order. Find the smallest range that
 * includes at least one number from each of the k lists.
 *
 * We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d -
 * c.
 *
 * ! nums.length == k
 * ! 1 <= k <= 3500
 * ! 1 <= nums[i].length <= 50
 * ! -10^5 <= nums[i][j] <= 10^5
 * ! nums[i] is sorted in non-decreasing order.
 */

class Solution {
public:
    std::vector<int> smallestRange(std::vector<std::vector<int>>& nums)
    {
        const int n = nums.size();
        std::set<std::tuple<int, int, int>> set;
        for (int i = 0; i < n; ++i) {
            set.emplace(nums[i][0], i, 0);
        }
        std::vector<int> result(2);
        int range = INT_MAX;
        while (true) {
            if (std::get<0>(*set.rbegin()) - std::get<0>(*set.begin()) < range) {
                range = std::get<0>(*set.rbegin()) - std::get<0>(*set.begin());
                result[0] = std::get<0>(*set.begin());
                result[1] = std::get<0>(*set.rbegin());
            }
            const auto [val, i, j] = *set.begin();
            if (j == nums[i].size() - 1)
                break;

            set.erase(set.begin());
            set.emplace(nums[i][j + 1], i, j + 1);
        }
        return result;
    }
};