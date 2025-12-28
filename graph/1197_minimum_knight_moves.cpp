#include <queue>
#include <unordered_map>
#include <vector>

/**
 * In an infinite chess board with coordinates from -infinity to +infinity, you have a knight at
 * square [0, 0].
 *
 * A knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a
 * cardinal direction, then one square in an orthogonal direction.
 *
 * Return the minimum number of steps needed to move the knight to the square [x, y]. It is
 * guaranteed the answer exists.
 *
 * ! -300 <= x, y <= 300
 * ! 0 <= |x| + |y| <= 300
 */

class Solution {
public:
    int minKnightMoves(int x, int y)
    {
        x = std::abs(x);
        y = std::abs(y);
        std::unordered_map<int, std::unordered_map<int, bool>> visited;
        visited[0][0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        int result = -1;
        while (!queue.empty()) {
            result++;
            for (int k = queue.size(); k > 0; --k) {
                const auto [i, j] = queue.front();
                queue.pop();
                if (i == x && j == y)
                    return result;

                for (const auto& [dx, dy] : kDirections) {
                    const int p = std::abs(i + dx);
                    const int q = std::abs(j + dy);
                    if (!visited.count(p) || !visited[p].count(q)) {
                        visited[p][q] = true;
                        queue.emplace(p, q);
                    }
                }
            }
        }
        return result;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2},
                                                       {1, 2},   {2, 1},   {2, -1}, {1, -2}};
};