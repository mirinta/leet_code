#include <array>
#include <vector>

/**
 * A room is represented by a 0-indexed 2D binary matrix room where a 0 represents an empty space
 * and a 1 represents a space with an object. The top left corner of the room will be empty in all
 * test cases.
 *
 * A cleaning robot starts at the top left corner of the room and is facing right. The robot will
 * continue heading straight until it reaches the edge of the room or it hits an object, after which
 * it will turn 90 degrees clockwise and repeat this process. The starting space and all spaces that
 * the robot visits are cleaned by it.
 *
 * Return the number of clean spaces in the room if the robot runs indefinitely.
 *
 * ! m == room.length
 * ! n == room[r].length
 * ! 1 <= m, n <= 300
 * ! room[r][c] is either 0 or 1.
 * ! room[0][0] == 0
 */

class Solution {
public:
    int numberOfCleanRooms(std::vector<std::vector<int>>& room)
    {
        const int m = room.size();
        const int n = room[0].size();
        std::vector<std::vector<std::array<bool, 4>>> visited(m, std::vector<std::array<bool, 4>>(n));
        std::vector<std::vector<bool>> cleaned(m, std::vector<bool>(n, false));
        return dfs(visited, cleaned, 0, 0, 0, room);
    }

private:
    int dfs(std::vector<std::vector<std::array<bool, 4>>>& visited,
            std::vector<std::vector<bool>>& cleaned,
            int i,
            int j,
            int heading,
            const std::vector<std::vector<int>>& room)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        if (visited[i][j][heading])
            return 0;

        visited[i][j][heading] = true;
        int result = 0;
        if (!cleaned[i][j]) {
            result++;
            cleaned[i][j] = true;
        }
        const auto& [dx, dy] = kDirections[heading];
        const int x = i + dx;
        const int y = j + dy;
        if (x < 0 || x >= room.size() || y < 0 || y >= room[0].size() || room[x][y] == 1)
            return result + dfs(visited, cleaned, i, j, (heading + 1) % 4, room);

        return result + dfs(visited, cleaned, x, y, heading, room);
    }
};