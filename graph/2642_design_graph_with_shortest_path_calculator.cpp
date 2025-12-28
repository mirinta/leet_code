#include <queue>
#include <vector>

/**
 * There is a directed weighted graph that consists of n nodes numbered from 0 to n - 1. The edges
 * of the graph are initially represented by the given array edges where edges[i] = [fromi, toi,
 * edgeCosti] meaning that there is an edge from fromi to toi with the cost edgeCosti.
 *
 * Implement the Graph class:
 *
 * - Graph(int n, int[][] edges) initializes the object with n nodes and the given edges.
 *
 * - addEdge(int[] edge) adds an edge to the list of edges where edge = [from, to, edgeCost]. It is
 * guaranteed that there is no edge between the two nodes before adding this one.
 *
 * - int shortestPath(int node1, int node2) returns the minimum cost of a path from node1 to node2.
 * If no path exists, return 1. The cost of a path is the sum of the costs of the edges in the path.
 *
 * ! 1 <= n <= 100
 * ! 0 <= edges.length <= n * (n - 1)
 * ! edges[i].length == edge.length == 3
 * ! 0 <= fromi, toi, from, to, node1, node2 <= n - 1
 * ! 1 <= edgeCosti, edgeCost <= 10^6
 * ! There are no repeated edges and no self-loops in the graph at any point.
 * ! At most 100 calls will be made for addEdge.
 * ! At most 100 calls will be made for shortestPath.
 */

class Graph {
public:
    Graph(int n, const std::vector<std::vector<int>>& edges) : graph(n)
    {
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
        }
    }

    void addEdge(const std::vector<int>& edge)
    {
        graph[edge[0]].emplace_back(edge[1], edge[2]);
    }

    int shortestPath(int node1, int node2)
    {
        // costs are positive numbers, we can use Dijkstra's algorithm
        std::vector<int> distTo(graph.size(), INT_MAX);
        distTo[node1] = 0;
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        pq.emplace(0, node1);
        while (!pq.empty()) {
            const auto [dist, v] = pq.top();
            pq.pop();
            if (v == node2)
                return dist;

            for (const auto& [w, cost] : graph[v]) {
                if (distTo[w] > distTo[v] + cost) {
                    distTo[w] = distTo[v] + cost;
                    pq.emplace(distTo[w], w);
                }
            }
        }
        return distTo[node2] == INT_MAX ? -1 : distTo[node2];
    }

private:
    using Pair = std::pair<int, int>; // <dist, v>
    static constexpr auto comparator = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
    std::vector<std::vector<std::pair<int, int>>> graph; // <vertex, cost>
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */