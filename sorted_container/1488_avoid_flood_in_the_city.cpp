#include <set>
#include <unordered_map>
#include <vector>

/**
 * Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it
 * rains over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full
 * of water, there will be a flood. Your goal is to avoid floods in any lake.
 *
 * Given an integer array rains where:
 *
 * - rains[i] > 0 means there will be rains over the rains[i] lake.
 *
 * - rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry
 * it.
 *
 * Return an array ans where:
 *
 * - ans.length == rains.length
 *
 * - ans[i] == -1 if rains[i] > 0.
 *
 * - ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
 *
 * If there are multiple valid answers return any of them. If it is impossible to avoid flood return
 * an empty array.
 *
 * Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty
 * lake, nothing changes.
 *
 * ! 1 <= rains.length <= 10^5
 * ! 0 <= rains[i] <= 10^9
 */

class Solution {
public:
    std::vector<int> avoidFlood(std::vector<int>& rains)
    {
        const int n = rains.size();
        std::unordered_map<int, int> map; // map[x] = i, lake x is filled in the ith day
        std::set<int> set;                // available days to dry a full lake
        std::vector<int> result(n, -1);
        for (int i = 0; i < n; ++i) {
            if (rains[i] == 0) {
                set.insert(i);
                continue;
            }
            if (map.count(rains[i])) {
                auto iter = set.lower_bound(map[rains[i]]);
                if (iter == set.end())
                    return {};

                result[*iter] = rains[i];
                set.erase(iter);
            }
            map[rains[i]] = i;
        }
        for (const auto& i : set) {
            result[i] = 1;
        }
        return result;
    }
};
