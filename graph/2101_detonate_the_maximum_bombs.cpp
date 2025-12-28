#include <queue>
#include <unordered_set>
#include <vector>

/**
 * You are given a list of bombs. The range of a bomb is defined as the area where its effect can be
 * felt. This area is in the shape of a circle with the center as the location of the bomb.
 *
 * The bombs are represented by a 0-indexed 2D integer array "bombs" where bombs[i] = [xi, yi, ri].
 * xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, wheras ri
 * denotes the radius of its range.
 *
 * You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs
 * that lie in its range. These bombs will further detonate the bombs that lie in their ranges.
 *
 * Given the list of bombs, return the maximum number of bombs that can be detonated if you are
 * allowed to detonate only one bomb.
 *
 * ! 1 <= bombs.length <= 100
 * ! bombs[i].length == 3
 * ! 1 <= xi, yi, ri <= 105
 */

class Solution {
public:
    int maximumDetonation(const std::vector<std::vector<int>>& bombs)
    {
        if (bombs.empty())
            return 0;

        const auto n = bombs.size();
        // graph[i]={bomb indices that can be detonated by bomb i}
        std::vector<std::vector<int>> graph(n, std::vector<int>{});
        for (int i = 0; i < n; ++i) {
            const long long r = bombs[i][2];
            const long long rSquared = r * r;
            for (int j = 0; j < n; ++j) {
                if (i == j)
                    continue;

                if (distanceSquared(bombs[i][0], bombs[i][1], bombs[j][0], bombs[j][1]) <= rSquared) {
                    graph[i].push_back(j);
                }
            }
        }
        // approach 1: DFS
        // int result = INT_MIN;
        // for (int src = 0; src < n; ++src) {
        //     std::unordered_set<int> visited;
        //     result = std::max(result, dfs(src, visited, graph));
        // }
        // return result;
        // approach 2: BFS
        return bfs(graph);
    }

private:
    long long distanceSquared(int x1, int y1, int x2, int y2)
    {
        const long long dx = x1 - x2;
        const long long dy = y1 - y2;
        return dx * dx + dy * dy;
    }

    int dfs(int src, std::unordered_set<int>& visited, const std::vector<std::vector<int>>& graph)
    {
        if (visited.count(src))
            return 0;

        visited.insert(src);
        for (const auto& adj : graph[src]) {
            dfs(adj, visited, graph);
        }
        return visited.size();
    }

    int bfs(const std::vector<std::vector<int>>& graph)
    {
        int result = INT_MIN;
        const auto n = graph.size();
        for (int i = 0; i < n; ++i) {
            std::queue<int> queue;
            queue.push(i);
            std::vector<bool> visited(n);
            visited[i] = true;
            int count = 0;
            while (!queue.empty()) {
                const auto detonate = queue.front();
                queue.pop();
                for (const auto& adjacent : graph[detonate]) {
                    if (!visited[adjacent]) {
                        queue.push(adjacent);
                        visited[adjacent] = true;
                    }
                }
                count++;
            }
            result = std::max(result, count);
        }
        return result;
    }
};