#include <queue>
#include <vector>

/**
 * You are given three positive integers n, x, and y.
 *
 * In a city, there exist houses numbered 1 to n connected by n streets. There is a street
 * connecting the house numbered i with the house numbered i + 1 for all 1 <= i <= n - 1 . An
 * additional street connects the house numbered x with the house numbered y.
 *
 * For each k, such that 1 <= k <= n, you need to find the number of pairs of houses (house1,
 * house2) such that the minimum number of streets that need to be traveled to reach house2 from
 * house1 is k.
 *
 * Return a 1-indexed array result of length n where result[k] represents the total number of pairs
 * of houses such that the minimum streets required to reach one house from the other is k.
 *
 * Note that x and y can be equal.
 *
 * ! 2 <= n <= 100
 * ! 1 <= x, y <= n
 */

class Solution {
public:
    std::vector<int> countOfPairs(int n, int x, int y)
    {
        std::vector<std::vector<int>> graph(n);
        for (int i = 1; i < n; ++i) {
            graph[i].push_back(i - 1);
            graph[i - 1].push_back(i);
        }
        graph[x - 1].push_back(y - 1);
        graph[y - 1].push_back(x - 1);
        std::vector<int> result(n, 0);
        for (int i = 0; i < n; ++i) {
            bfs(result, i, graph);
        }
        return result;
    }

private:
    void bfs(std::vector<int>& result, int start, const std::vector<std::vector<int>>& graph)
    {
        std::queue<int> queue;
        queue.push(start);
        std::vector<bool> visited(graph.size(), false);
        visited[start] = true;
        int k = 1;
        while (!queue.empty()) {
            for (int sz = queue.size(); sz > 0; --sz) {
                const auto v = queue.front();
                queue.pop();
                for (const auto& w : graph[v]) {
                    if (!visited[w]) {
                        result[k - 1]++;
                        visited[w] = true;
                        queue.push(w);
                    }
                }
            }
            k++;
        }
    }
};