#include <queue>
#include <unordered_map>
#include <vector>

/**
 * There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given
 * a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an
 * edge between nodes ai and bi in the tree.
 *
 * At every node i, there is a gate. You are also given an array of even integers amount, where
 * amount[i] represents:
 *
 * - the price needed to open the gate at node i, if amount[i] is negative, or,
 *
 * - the cash reward obtained on opening the gate at node i, otherwise.
 *
 * The game goes on as follows:
 *
 * - Initially, Alice is at node 0 and Bob is at node bob.
 *
 * - At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf
 * node, while Bob moves towards node 0.
 *
 * - For every node along their path, Alice and Bob either spend money to open the gate at that
 * node, or accept the reward. Note that:
 *
 *   - If the gate is already open, no price will be required, nor will there be any cash reward.
 *
 *   - If Alice and Bob reach the node simultaneously, they share the price/reward for opening the
 * gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2
 * each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
 *
 * - If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops
 * moving. Note that these events are independent of each other.
 *
 * Return the maximum net income Alice can have if she travels towards the optimal leaf node.
 *
 * ! 2 <= n <= 10^5
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 0 <= ai, bi < n
 * ! ai != bi
 * ! edges represents a valid tree.
 * ! 1 <= bob < n
 * ! amount.length == n
 * ! amount[i] is an even integer in the range [-10^4, 10^4].
 */

class Solution
{
public:
    int mostProfitablePath(std::vector<std::vector<int>>& edges, int bob, std::vector<int>& amount)
    {
        const int n = edges.size() + 1;
        std::vector<std::vector<int>> graph(n);
        for (const auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        std::unordered_map<int, int> bobPath; // <vertex, time arrived>
        std::vector<bool> visited(n, false);
        dfs(bobPath, visited, bob, 0, graph);
        visited.assign(n, false);
        std::queue<std::tuple<int, int, int>> queue; // <vertex, time, income>
        queue.emplace(0, 0, 0);
        int result = INT_MIN;
        while (!queue.empty()) {
            auto [v, time, income] = queue.front();
            queue.pop();
            visited[v] = true;
            if (!bobPath.count(v) || time < bobPath[v]) {
                income += amount[v];
            } else if (time == bobPath[v]) {
                income += amount[v] / 2;
            }
            if (graph[v].size() == 1 && v != 0) {
                result = std::max(result, income);
            }
            for (const auto& adj : graph[v]) {
                if (!visited[adj]) {
                    queue.emplace(adj, time + 1, income);
                }
            }
        }
        return result;
    }

private:
    bool dfs(std::unordered_map<int, int>& map, std::vector<bool>& visited, int v, int time,
             const std::vector<std::vector<int>>& graph)
    {
        visited[v] = true;
        map[v] = time;
        if (v == 0)
            return true;

        for (const auto& w : graph[v]) {
            if (visited[w])
                continue;

            if (dfs(map, visited, w, time + 1, graph))
                return true;
        }
        visited[v] = false;
        map.erase(v);
        return false;
    }
};
