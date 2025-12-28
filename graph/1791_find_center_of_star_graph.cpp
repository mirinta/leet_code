#include <vector>

/**
 * There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a
 * graph where there is one center node and exactly n - 1 edges that connect the center node with
 * every other node.
 *
 * You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an
 * edge between the nodes ui and vi. Return the center of the given star graph.
 *
 * ! 3 <= n <= 10^5
 * ! edges.length == n - 1
 * ! edges[i].length == 2
 * ! 1 <= ui, vi <= n
 * ! ui != vi
 * ! The given edges represent a valid star graph.
 */

class Solution {
public:
    int findCenter(std::vector<std::vector<int>>& edges)
    {
        const int n = edges.size() + 1;
        std::vector<int> degrees(n);
        for (const auto& edge : edges) {
            degrees[edge[0] - 1]++;
            degrees[edge[1] - 1]++;
        }
        for (int i = 0; i < n; ++i) {
            if (degrees[i] == n - 1)
                return i + 1;
        }
        return -1;
    }
};