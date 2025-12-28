#include <unordered_map>
#include <vector>

/**
 * You are given a positive integer n, representing an n x n city. You are also given a 2D grid
 * buildings, where buildings[i] = [x, y] denotes a unique building located at coordinates [x, y].
 *
 * A building is covered if there is at least one building in all four directions: left, right,
 * above, and below.
 *
 * Return the number of covered buildings.
 *
 * ! 2 <= n <= 10^5
 * ! 1 <= buildings.length <= 10^5
 * ! buildings[i] = [x, y]
 * ! 1 <= x, y <= n
 * ! All coordinates of buildings are unique.
 */

class Solution {
public:
    int countCoveredBuildings(int n, std::vector<std::vector<int>>& buildings)
    {
        std::unordered_map<int, std::tuple<int, int, int>> X; // <count, minY, maxY>
        std::unordered_map<int, std::tuple<int, int, int>> Y; // <count, minX, maxX>
        for (const auto& b : buildings) {
            update(X, b[0], b[1]);
            update(Y, b[1], b[0]);
        }
        int result = 0;
        for (const auto& b : buildings) {
            result += check(X, b[0], b[1]) && check(Y, b[1], b[0]);
        }
        return result;
    }

private:
    void update(std::unordered_map<int, std::tuple<int, int, int>>& map, int key, int val)
    {
        if (!map.count(key)) {
            map[key] = std::make_tuple(0, INT_MAX, INT_MIN);
        }
        auto& [count, min, max] = map[key];
        count++;
        min = std::min(min, val);
        max = std::max(max, val);
    }

    bool check(const std::unordered_map<int, std::tuple<int, int, int>>& map, int key, int val)
    {
        if (!map.count(key))
            return false;

        const auto& [count, min, max] = map.at(key);
        return count >= 3 && min != val && max != val;
    }
};