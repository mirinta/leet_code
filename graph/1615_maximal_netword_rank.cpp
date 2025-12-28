#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * There is an infrastructure of n cities with some number of roads connecting these cities. Each
 * roads[i] = [ai, bi] indicates that there is a bidirectional road between cities ai and bi.
 *
 * The network rank of two different cities is defined as the total number of directly connected
 * roads to either city. If a road is directly connected to both cities, it is only counted once.
 *
 * The maximal network rank of the infrastructure is the maximum network rank of all pairs of
 * different cities.
 *
 * Given the integer n and the array roads, return the maximal network rank of the entire
 * infrastructure.
 *
 * ! 2 <= n <= 100
 * ! 0 <= roads.length <= n * (n - 1) / 2
 * ! roads[i].length == 2
 * ! 0 <= ai, bi <= n-1
 * ! ai != bi
 * ! Each pair of cities has at most one road connecting them.
 */

class Solution {
public:
    // time O(E+V^2), space O(E)
    int maximalNetworkRank(int n, std::vector<std::vector<int>>& roads)
    {
        std::vector<int> degrees(n, 0);
        std::unordered_map<int, std::unordered_set<int>> directlyConnected;
        for (const auto& road : roads) {
            degrees[road[0]]++;
            degrees[road[1]]++;
            directlyConnected[road[0]].insert(road[1]);
            directlyConnected[road[1]].insert(road[0]);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (directlyConnected[i].count(j)) {
                    result = std::max(result, degrees[i] + degrees[j] - 1);
                } else {
                    result = std::max(result, degrees[i] + degrees[j]);
                }
            }
        }
        return result;
    }
};