#include <unordered_map>
#include <vector>

/**
 * There are n people that are split into some unknown number of groups. Each person is labeled with
 * a unique ID from 0 to n - 1.
 *
 * You are given an integer array groupSizes, where groupSizes[i] is the size of the group that
 * person i is in. For example, if groupSizes[1] = 3, then person 1 must be in a group of size 3.
 *
 * Return a list of groups such that each person i is in a group of size groupSizes[i].
 *
 * Each person should appear in exactly one group, and every person must be in a group. If there are
 * multiple answers, return any of them. It is guaranteed that there will be at least one valid
 * solution for the given input.
 *
 * ! groupSizes.length == n
 * ! 1 <= n <= 500
 * ! 1 <= groupSizes[i] <= n
 */

class Solution {
public:
    std::vector<std::vector<int>> groupThePeople(std::vector<int>& groupSizes)
    {
        const int n = groupSizes.size();
        std::unordered_map<int, std::vector<int>> map; // group size to indices
        for (int i = 0; i < n; ++i) {
            map[groupSizes[i]].push_back(i);
        }
        std::vector<std::vector<int>> result;
        for (const auto& [size, indices] : map) {
            for (int i = 0; i + size <= indices.size(); i += size) {
                std::vector<int> group;
                group.reserve(size);
                for (int j = 0; j < size; ++j) {
                    group.push_back(indices[i + j]);
                }
                result.push_back(std::move(group));
            }
        }
        return result;
    }
};
