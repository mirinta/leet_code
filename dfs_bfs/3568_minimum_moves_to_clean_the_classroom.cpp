#include <array>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

/**
 * You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around
 * the room. Each cell in the grid is one of the following:
 *
 * - 'S': Starting position of the student
 *
 * - 'L': Litter that must be collected (once collected, the cell becomes empty)
 *
 * - 'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can
 * be used multiple times)
 *
 * - 'X': Obstacle the student cannot pass through
 *
 * - '.': Empty space
 *
 * You are also given an integer energy, representing the student's maximum energy capacity. The student starts with
 * this energy from the starting position 'S'.
 *
 * Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student
 * can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
 *
 * Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
 *
 * ! 1 <= m == classroom.length <= 20
 * ! 1 <= n == classroom[i].length <= 20
 * ! classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
 * ! 1 <= energy <= 50
 * ! There is exactly one 'S' in the grid.
 * ! There are at most 10 'L' cells in the grid.
 */

class Solution {
public:
    int minMoves(std::vector<std::string>& classroom, int energy)
    {
        static constexpr std::array<std::array<int, 2>, 4> kDirections{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};
        const int m = classroom.size();
        const int n = classroom[0].size();
        int startX = -1;
        int startY = -1;
        int count = 0;
        std::vector<std::vector<int>> code(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    startX = i;
                    startY = j;
                } else if (classroom[i][j] == 'L') {
                    code[i][j] = 1 << count;
                    count++;
                }
            }
        }
        const int target = (1 << count) - 1;
        std::vector best(m, std::vector<std::vector<int>>(n, std::vector<int>(1 << count, -1)));
        best[startX][startY][0] = energy;
        std::queue<std::tuple<int, int, int, int, int>> queue;
        queue.emplace(startX, startY, 0, energy, 0);
        while (!queue.empty()) {
            const auto [x, y, mask, remaining, steps] = queue.front();
            queue.pop();
            if (mask == target)
                return steps;

            if (remaining == 0)
                continue;

            for (const auto& [dx, dy] : kDirections) {
                const int nX = x + dx;
                const int nY = y + dy;
                if (nX >= m || nX < 0 || nY >= n || nY < 0)
                    continue;

                if (classroom[nX][nY] == 'X')
                    continue;

                const int nRemaining = classroom[nX][nY] == 'R' ? energy : remaining - 1;
                const int nMask = mask | code[nX][nY];
                if (nRemaining > best[nX][nY][nMask]) {
                    best[nX][nY][nMask] = nRemaining;
                    queue.emplace(nX, nY, nMask, nRemaining, steps + 1);
                }
            }
        }
        return -1;
    }
};
