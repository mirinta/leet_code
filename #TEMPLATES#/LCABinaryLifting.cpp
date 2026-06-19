#include <bit>
#include <functional>
#include <vector>

class LCABinaryLifting {
public:
    /**
     * @brief Construct a new LCABinaryLifting object
     *
     * @param root 0-indexed
     * @param n
     * @param graph adjacent matrix
     */
    explicit LCABinaryLifting(int root, int n, const std::vector<std::vector<int>>& graph)
        : parent(n, std::vector<int>(std::ceil(std::log(n) / std::log(2)), -1)), depth(n, 0)
    {
        std::function<void(int, int)> dfs = [&](int curr, int prev) {
            parent[curr][0] = prev;
            for (const auto& next : graph[curr]) {
                if (next == prev)
                    continue;

                depth[next] = depth[curr] + 1;
                dfs(next, curr);
            }
        };
        dfs(root, -1);
        for (int i = 0; i < parent[0].size() - 1; ++i) {
            for (int x = 0; x < n; ++x) {
                if (const int p = parent[x][i]; p != -1) {
                    parent[x][i + 1] = parent[p][i];
                }
            }
        }
    }

    /**
     * @brief Get the Kth Ancestor object
     *
     * @param x 0-indexed
     * @param k 1-indexed
     * @return int
     */
    int getKthAncestor(int x, int k)
    {
        for (int i = 0; i < parent[x].size(); ++i) {
            if (k & (1 << i)) {
                x = parent[x][i];
            }
        }
        return x;
    }

    /**
     * @brief Get the Lowest Common Ancestor of node x and node y
     *
     * @param x 0-indexed
     * @param y 0-indexed
     * @return int
     */
    int lca(int x, int y)
    {
        if (depth[x] > depth[y]) {
            std::swap(x, y);
        }
        y = getKthAncestor(y, depth[y] - depth[x]);
        if (x == y)
            return x;

        for (int i = parent[x].size() - 1; i >= 0; --i) {
            if (parent[x][i] == -1 || parent[x][i] == parent[y][i])
                continue;

            x = parent[x][i];
            y = parent[y][i];
        }
        return parent[x][0];
    }

    /**
     * @brief Get the distance (number of edges) between node x and node y
     *
     * @param x 0-indexed
     * @param y 0-indexed
     * @return int
     */
    int dist(int x, int y)
    {
        return depth[x] + depth[y] - 2 * depth[lca(x, y)];
    }

private:
    std::vector<std::vector<int>> parent;
    std::vector<int> depth;
};