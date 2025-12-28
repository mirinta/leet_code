#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer n denoting the total number of servers and a 2D 0-indexed integer array
 * logs, where logs[i] = [server_id, time] denotes that the server with id server_id received a
 * request at time time.
 *
 * You are also given an integer x and a 0-indexed integer array queries.
 *
 * Return a 0-indexed integer array arr of length queries.length where arr[i] represents the number
 * of servers that did not receive any requests during the time interval [queries[i] - x,
 * queries[i]].
 *
 * Note that the time intervals are inclusive.
 *
 * ! 1 <= n <= 10^5
 * ! 1 <= logs.length <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! logs[i].length == 2
 * ! 1 <= logs[i][0] <= n
 * ! 1 <= logs[i][1] <= 10^6
 * ! 1 <= x <= 10^5
 * ! x < queries[i] <= 10^6
 */

class Solution {
public:
    std::vector<int> countServers(int n, std::vector<std::vector<int>>& logs, int x, std::vector<int>& queries)
    {
        std::sort(logs.begin(), logs.end(), [](const auto& log1, const auto& log2) { return log1[1] < log2[1]; });
        std::vector<std::pair<int, int>> queryPairs;
        for (int i = 0; i < queries.size(); ++i) {
            queryPairs.emplace_back(queries[i], i);
        }
        std::sort(queryPairs.begin(), queryPairs.end());

        std::vector<int> result(queries.size(), 0);
        std::unordered_map<int, int> map;
        int i = 0;
        int j = 0;
        for (const auto& [query, index] : queryPairs) {
            int start = query - x;
            int end = query;
            while (j < logs.size() && logs[j][1] <= end) {
                map[logs[j][0]]++;
                j++;
            }
            while (i < logs.size() && logs[i][1] < start) {
                if (map[logs[i][0]] == 1) {
                    map.erase(logs[i][0]);
                } else {
                    map[logs[i][0]]--;
                }
                i++;
            }
            result[index] = n - map.size();
        }
        return result;
    }
};
