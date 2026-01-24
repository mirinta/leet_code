#include <map>
#include <set>
#include <vector>

/**
 * Given an array nums, you can perform the following operation any number of times:
 *
 * - Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
 *
 * - Replace the pair with their sum.
 *
 * Return the minimum number of operations needed to make the array non-decreasing.
 *
 * An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it
 * exists).
 *
 * ! 1 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minimumPairRemoval(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::set<std::pair<long long, int>> set;            // <sum, id>
        std::map<int, std::pair<long long, long long>> map; // id to <left, right>
        int invalid = 0;
        for (int i = 0; i + 1 < n; ++i) {
            invalid += nums[i] > nums[i + 1];
            set.emplace(nums[i] + nums[i + 1], i);
            map[i] = {nums[i], nums[i + 1]};
        }
        int result = 0;
        while (invalid > 0 && !set.empty()) {
            result++;
            const auto [sum, id] = *set.begin();
            set.erase(set.begin());
            invalid -= map[id].first > map[id].second;
            auto iter = map.find(id);
            if (iter != map.begin()) {
                const int prevId = std::prev(iter)->first;
                auto& [prevLeft, prevRight] = map[prevId];
                invalid -= prevLeft > prevRight;
                set.erase(set.find({prevLeft + prevRight, prevId}));
                prevRight = sum;
                invalid += prevLeft > prevRight;
                set.emplace(prevLeft + prevRight, prevId);
            }
            if (std::next(iter) != map.end()) {
                const int nextId = std::next(iter)->first;
                auto& [nextLeft, nextRight] = map[nextId];
                invalid -= nextLeft > nextRight;
                set.erase(set.find({nextLeft + nextRight, nextId}));
                nextLeft = sum;
                invalid += nextLeft > nextRight;
                set.emplace(nextLeft + nextRight, nextId);
            }
            map.erase(id);
        }
        return result;
    }
};