#include <functional>
#include <stack>
#include <vector>

using Graph = const std::vector<std::vector<int>>;

std::vector<std::pair<int, int>> findEdges(const Graph& graph)
{
    const int n = graph.size();
    int time = 0;
    std::vector<int> dfn(n, -1);
    std::vector<int> low(n, -1);
    std::vector<std::pair<int, int>> result;
    // -----------------------------------------------------------------
    std::function<void(int, int)> dfs = [&](int current, int parent) {
        dfn[current] = low[current] = ++time;
        for (const auto& next : graph[current]) {
            if (next == parent)
                continue;

            if (dfn[next] == -1) {
                dfs(next, current);
                if (low[next] > dfn[current]) {
                    result.emplace_back(current, next);
                }
                low[current] = std::min(low[current], low[next]);
            } else {
                low[current] = std::min(low[current], dfn[next]);
            }
        }
    };
    // -----------------------------------------------------------------
    for (int i = 0; i < n; ++i) {
        if (dfn[i] == -1) {
            dfs(i, -1);
        }
    }
    return result;
}
