#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path
 * going from cityAi to cityBi. Return the destination city, that is, the city without any path
 * outgoing to another city.
 *
 * It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be
 * exactly one destination city.
 *
 * ! 1 <= paths.length <= 100
 * ! paths[i].length == 2
 * ! 1 <= cityAi.length, cityBi.length <= 10
 * ! cityAi != cityBi
 * ! All strings consist of lowercase and uppercase English letters and the space character.
 */

class Solution {
public:
    std::string destCity(std::vector<std::vector<std::string>>& paths)
    {
        return approach2(paths);
    }

private:
    std::string approach2(std::vector<std::vector<std::string>>& paths)
    {
        // put all src into a hash set
        // the final answer must not be in the hash set
        std::unordered_set<std::string> set;
        for (const auto& path : paths) {
            set.insert(path[0]);
        }
        for (const auto& path : paths) {
            if (!set.count(path[1]))
                return path[1];
        }
        return {};
    }

    std::string approach1(std::vector<std::vector<std::string>>& paths)
    {
        std::unordered_map<std::string, int> map;
        for (const auto& path : paths) {
            map[path[0]]--;
            map[path[1]]++;
        }
        for (const auto& [name, degree] : map) {
            if (degree > 0)
                return name;
        }
        return {};
    }
};