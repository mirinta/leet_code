#include <string>
#include <unordered_set>

/**
 * Given a string path, where path[i] = 'N', 'S', 'E' or 'W', each representing moving one unit
 * north, south, east, or west, respectively. You start at the origin (0, 0) on a 2D plane and walk
 * on the path specified by path.
 *
 * Return true if the path crosses itself at any point, that is, if at any time you are on a
 * location you have previously visited. Return false otherwise.
 *
 * ! 1 <= path.length <= 10^4
 * ! path[i] is either 'N', 'S', 'E', or 'W'.
 */

class Solution {
public:
    bool isPathCrossing(std::string path)
    {
        std::unordered_set<std::string> coords;
        coords.insert(encode(0, 0));
        int x = 0;
        int y = 0;
        for (const auto& c : path) {
            if (c == 'N') {
                y++;
            } else if (c == 'S') {
                y--;
            } else if (c == 'E') {
                x++;
            } else if (c == 'W') {
                x--;
            }
            if (coords.count(encode(x, y)))
                return true;

            coords.insert(encode(x, y));
        }
        return false;
    }

private:
    std::string encode(int x, int y)
    {
        return std::to_string(x) + "," + std::to_string(y);
    }
};