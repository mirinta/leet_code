#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You have information about n different recipes. You are given a string array recipes and a 2D
 * string array ingredients. The ith recipe has the name recipes[i], and you can create it if you
 * have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other
 * recipes, i.e., ingredients[i] may contain a string that is in recipes.
 *
 * You are also given a string array supplies containing all the ingredients that you initially
 * have, and you have an infinite supply of all of them.
 *
 * Return a list of all the recipes that you can create. You may return the answer in any order.
 *
 * Note that two recipes may contain each other in their ingredients.
 *
 * ! n == recipes.length == ingredients.length
 * ! 1 <= n <= 100
 * ! 1 <= ingredients[i].length, supplies.length <= 100
 * ! 1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
 * ! recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
 * ! All the values of recipes and supplies combined are unique.
 * ! Each ingredients[i] does not contain any duplicate values.
 */

class Solution {
public:
    std::vector<std::string> findAllRecipes(std::vector<std::string>& recipes,
                                            std::vector<std::vector<std::string>>& ingredients,
                                            std::vector<std::string>& supplies)
    {
        std::unordered_set<std::string> set(supplies.begin(), supplies.end());
        std::unordered_map<std::string, std::vector<std::string>> graph;
        std::unordered_map<std::string, int> map; // recipe to index
        std::vector<int> indegree(recipes.size(), 0);
        for (int i = 0; i < recipes.size(); ++i) {
            for (const auto& s : ingredients[i]) {
                if (!set.count(s)) {
                    graph[s].push_back(recipes[i]);
                    indegree[i]++;
                }
            }
            map[recipes[i]] = i;
        }
        std::queue<int> queue;
        for (int i = 0; i < recipes.size(); ++i) {
            if (indegree[i] == 0) {
                queue.push(i);
            }
        }
        std::vector<std::string> result;
        while (!queue.empty()) {
            const auto idx = queue.front();
            queue.pop();
            result.push_back(recipes[idx]);
            if (!graph.count(recipes[idx]))
                continue;

            for (const auto& s : graph[recipes[idx]]) {
                if (--indegree[map[s]] == 0) {
                    queue.push(map[s]);
                }
            }
        }
        return result;
    }
};
