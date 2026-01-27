#include <vector>

/**
 * @brief Adjacency matrix (0-indexed square matrix).
 *
 * @note graph[i][x] = {j, w} indicates that there is an directed edge from vertex i to vertex j
 * with weight w.
 */
using Graph = std::vector<std::vector<std::pair<int, long long>>>;

using Edges = std::vector<std::tuple<int, int, long long>>; // <from, to, weight>