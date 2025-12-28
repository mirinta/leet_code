#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * There are n items each belonging to zero or one of m groups where group[i] is the group that the
 * i-th item belongs to and it's equal to -1 if the i-th item belongs to no group. The items and the
 * groups are zero indexed. A group can have no item belonging to it.
 *
 * Return a sorted list of the items such that:
 *
 * - The items that belong to the same group are next to each other in the sorted list.
 *
 * - There are some relations between these items where beforeItems[i] is a list containing all the
 * items that should come before the i-th item in the sorted array (to the left of the i-th item).
 *
 * Return any solution if there is more than one solution and return an empty list if there is no
 * solution.
 *
 * ! 1 <= m <= n <= 3 * 10^4
 * ! group.length == beforeItems.length == n
 * ! -1 <= group[i] <= m - 1
 * ! 0 <= beforeItems[i].length <= n - 1
 * ! 0 <= beforeItems[i][j] <= n - 1
 * ! i != beforeItems[i][j]
 * ! beforeItems[i] does not contain duplicates elements.
 */

class Solution {
    using Graph = std::unordered_map<int, std::unordered_set<int>>;

public:
    std::vector<int> sortItems(int n, int m, std::vector<int>& group, std::vector<std::vector<int>>& beforeItems)
    {
        // reassign group ID
        for (int i = 0, j = m; i < n; ++i) {
            if (group[i] == -1) {
                group[i] = j++;
            }
        }
        // build graphs
        Graph graphAmongGroups;
        std::unordered_map<int, Graph> graphWithinGroup;
        for (const auto& groupId : group) {
            graphAmongGroups[groupId] = {};
            graphWithinGroup[groupId] = {};
        }
        for (int i = 0; i < n; ++i) {
            if (!graphWithinGroup[group[i]].count(i)) {
                graphWithinGroup[group[i]][i] = {};
            }
        }
        for (int i = 0; i < n; ++i) {
            for (const auto& j : beforeItems[i]) {
                if (group[i] != group[j]) {
                    graphAmongGroups[group[j]].insert(group[i]);
                } else {
                    graphWithinGroup[group[i]][j].insert(i);
                }
            }
        }
        // apply topological sorting
        const auto sortedGroups = topologicalSort(graphAmongGroups);
        if (sortedGroups.empty())
            return {};

        std::vector<int> result;
        for (const auto& groupId : sortedGroups) {
            const auto sortedItems = topologicalSort(graphWithinGroup[groupId]);
            if (sortedItems.empty())
                return {};

            for (const auto& item : sortedItems) {
                result.push_back(item);
            }
        }
        return result;
    }

private:
    // make sure input graph contains all vertices, return empty array if there's a cycle
    std::vector<int> topologicalSort(const Graph& graph)
    {
        std::unordered_map<int, int> indegree;
        for (const auto& [v, adjacencies] : graph) {
            if (adjacencies.count(v))
                return {}; // found self-loop

            if (!indegree.count(v)) {
                indegree[v] = 0;
            }
            for (const auto& adj : adjacencies) {
                indegree[adj]++;
            }
        }
        std::queue<int> queue;
        for (const auto& [v, val] : indegree) {
            if (val == 0) {
                queue.push(v);
            }
        }
        std::vector<int> result;
        while (!queue.empty()) {
            const auto v = queue.front();
            queue.pop();
            result.push_back(v);
            for (const auto& adj : graph.at(v)) {
                if (--indegree[adj] == 0) {
                    queue.push(adj);
                }
            }
        }
        if (result.size() != graph.size())
            return {};

        return result;
    }
};