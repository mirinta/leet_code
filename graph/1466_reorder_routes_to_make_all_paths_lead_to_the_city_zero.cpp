#include <queue>
#include <unordered_set>
#include <vector>

/**
 * There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to
 * travel between two different cities (this network form a tree). Last year, The ministry of
 * transport decided to orient the roads in one direction because they are too narrow.
 *
 * Roads are represented by connections where connections[i] = [ai, bi] represents a road from city
 * ai to city bi.
 *
 * This year, there will be a big event in the capital (city 0), and many people want to travel to
 * this city.
 *
 * Your task consists of reorienting some roads such that each city can visit the city 0. Return the
 * minimum number of edges changed.
 *
 * It's guaranteed that each city can reach city 0 after reorder.
 *
 * ! 2 <= n <= 5 * 10^4
 * ! connections.length == n - 1
 * ! connections[i].length == 2
 * ! 0 <= ai, bi <= n - 1
 * ! ai != bi
 */

class Solution {
public:
    int minReorder(int n, std::vector<std::vector<int>>& connections)
    {
        std::vector<std::vector<std::pair<int, int>>> graph(n);
        for (const auto& connection : connections) {
            const auto& from = connection[0];
            const auto& to = connection[1];
            graph[from].emplace_back(to, 1); // 1 means it is an original edge
            graph[to].emplace_back(from, 0); // 0 means it isn't an original edge
        }
        std::queue<int> queue;
        queue.push(0);
        std::vector<bool> visited(n, false);
        visited[0] = true;
        int result = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& [adj, flag] : graph[v]) {
                    if (visited[adj])
                        continue;

                    result += flag;
                    visited[adj] = true;
                    queue.push(adj);
                }
            }
        }
        return result;
    }
};
