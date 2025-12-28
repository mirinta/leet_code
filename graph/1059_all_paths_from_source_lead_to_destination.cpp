#include <unordered_set>
#include <vector>

/**
 * Given the edges of a directed graph where edges[i] = [ai, bi] indicates there is an edge between
 * nodes ai and bi, and two nodes source and destination of this graph, determine whether or not all
 * paths starting from source eventually, end at destination, that is:
 *
 * - At least one path exists from the source node to the destination node
 *
 * - If a path exists from the source node to a node with no outgoing edges, then that node is equal
 * to destination.
 *
 * - The number of possible paths from source to destination is a finite number. Return true
 * if and only if all roads from source lead to destination.
 *
 * ! 1 <= n <= 10^4
 * ! 0 <= edges.length <= 10^4
 * ! edges.length == 2
 * ! 0 <= ai, bi <= n - 1
 * ! 0 <= source <= n - 1
 * ! 0 <= destination <= n - 1
 * ! The given graph may have self-loops and parallel edges.
 */

class Solution {
public:
    bool leadsToDestination(int n, std::vector<std::vector<int>>& edges, int source, int destination)
    {
        std::vector<std::vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }
        std::vector<Color> colors(n, White);
        return dfs(colors, source, destination, graph);
    }

private:
    // White = not processed
    // Gray = being processed
    // Black = fully processed
    enum Color { White, Gray, Black };

    bool dfs(std::vector<Color>& colors, int current, int target, const std::vector<std::vector<int>>& graph)
    {
        if (graph[current].empty())
            return current == target;

        colors[current] = Gray;
        for (const auto& adj : graph[current]) {
            if (colors[adj] == Gray)
                return false;

            if (colors[adj] == White && !dfs(colors, adj, target, graph))
                return false;
        }
        colors[current] = Black;
        return true;
    }
};