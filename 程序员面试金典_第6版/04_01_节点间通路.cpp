#include <unordered_set>
#include <vector>

/**
 * 节点间通路。给定有向图，设计一个算法，找出两个节点之间是否存在一条路径。
 *
 * ! 节点数量n在[0, 1e5]范围内。
 * ! 节点编号大于等于 0 小于 n。
 * ! 图中可能存在自环和平行边。
 */

class Solution {
public:
    bool findWhetherExistsPath(int n, std::vector<std::vector<int>>& graph, int start, int target)
    {
        std::vector<std::unordered_set<int>> adjacency(n);
        for (const auto& edge : graph) {
            if (edge[0] != edge[1]) {
                adjacency[edge[0]].insert(edge[1]);
            }
        }
        std::vector<bool> visited(n, false);
        return dfs(visited, start, target, adjacency);
    }

private:
    bool dfs(std::vector<bool>& visited, int curr, int target, const std::vector<std::unordered_set<int>>& adjacency)
    {
        if (curr == target)
            return true;

        visited[curr] = true;
        for (const auto& adj : adjacency[curr]) {
            if (!visited[adj] && dfs(visited, adj, target, adjacency))
                return true;
        }
        return false;
    }
};