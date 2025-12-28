#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given a list of airline tickets where tickets[i] = [from_i, to_i] represent the departure
 * and the arrival airports of one flight. Reconstruct the itinerary in order and return it.
 *
 * All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with
 * "JFK". If there are multiple valid itineraries, you should return the itinerary that has the
 * smallest lexical order when read as a single string.
 *
 * For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 * You may assume all tickets form at least one valid itinerary. You must use all the tickets once
 * and only once.
 *
 * ! 1 <= tickets.length <= 300
 * ! tickets[i].length == 2
 * ! from_i.length == 3
 * ! to_i.length == 3
 * ! from_i and to_i consist of uppercase English letters.
 * ! from_i != to_i
 */

class Solution {
public:
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets)
    {
        std::unordered_map<std::string, std::vector<std::string>> graph;
        for (const auto& t : tickets) {
            graph[t[0]].push_back(t[1]);
        }
        for (auto& [from, destinations] : graph) {
            std::sort(destinations.begin(), destinations.end());
        }
        std::vector<std::string> result;
        std::function<void(std::string)> dfs = [&](const std::string& start) {
            while (!graph[start].empty()) {
                const auto next = graph[start].front();
                graph[start].erase(graph[start].begin());
                dfs(next);
            }
            result.push_back(start);
        };
        dfs("JFK");
        std::reverse(result.begin(), result.end());
        return result;
    }

private:
    // backtrack, TLE
    std::vector<std::string> approach1(std::vector<std::vector<std::string>>& tickets)
    {
        std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph;
        std::unordered_set<int> unused;
        for (int i = 0; i < tickets.size(); ++i) {
            const auto& from = tickets[i][0];
            const auto& to = tickets[i][1];
            graph[from].emplace_back(to, i);
            unused.insert(i);
        }
        for (auto& [from, destinations] : graph) {
            std::sort(destinations.begin(), destinations.end(),
                      [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        }
        std::vector<std::string> result{"JFK"};
        std::function<bool(std::string)> backtrack = [&](std::string start) {
            if (unused.empty())
                return true;

            if (!graph.count(start))
                return false;

            for (const auto& [to, id] : graph[start]) {
                if (!unused.count(id))
                    continue;

                unused.erase(id);
                result.push_back(to);
                if (backtrack(to))
                    return true;

                unused.insert(id);
                result.pop_back();
            }
            return false;
        };
        backtrack("JFK");
        return result;
    }
};
