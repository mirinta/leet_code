#include <functional>
#include <unordered_map>
#include <vector>

class Solve {
public:
    explicit Solve(const std::vector<std::pair<int, int>>& edges)
    {
        for (const auto& [from, to] : edges) {
            graph[from].push_back(to);
            degrees[from].second++;
            degrees[from].first++;
        }
    }

    bool hasEulerianPath() const
    {
        if (graph.empty())
            return false;

        int countOutMinusInEq1 = 0;
        int countInMinusOutEq1 = 0;
        for (const auto& [v, degree] : degrees) {
            const auto [in, out] = degree;
            if (std::abs(in - out) > 1)
                return false;

            countOutMinusInEq1 += out - in == 1;
            countInMinusOutEq1 += in - out == 1;
            if (countOutMinusInEq1 > 1 || countInMinusOutEq1 > 1)
                return false;
        }
        return true;
    }

    std::vector<int> findEulerianPath()
    {
        if (!hasEulerianPath())
            return {};

        int start = graph.begin()->first;
        for (const auto& [v, degree] : degrees) {
            if (degree.second - degree.first == 1) {
                start = v;
                break;
            }
        }
        std::vector<int> result;
        std::function<void(int)> dfs = [&](int start) {
            while (!graph[start].empty()) {
                const int next = graph[start].back();
                graph[start].pop_back();
                dfs(next);
            }
            result.push_back(start);
        };
        dfs(start);
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, std::pair<int, int>> degrees; // <in, out>
};
