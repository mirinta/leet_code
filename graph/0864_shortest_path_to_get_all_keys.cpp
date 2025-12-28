#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

/**
 * You are given an m x n grid grid where:
 *
 * - '.' is an empty cell.
 *
 * - '#' is a wall.
 *
 * - '@' is the starting point.
 *
 * - Lowercase letters represent keys.
 *
 * - Uppercase letters represent locks.
 *
 * You start at the starting point and one move consists of walking one space in one of the four
 * cardinal directions. You cannot walk outside the grid, or walk into a wall.
 *
 * If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its
 * corresponding key.
 *
 * For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k
 * letters of the English alphabet in the grid. This means that there is exactly one key for each
 * lock, and one lock for each key; and also that the letters used to represent the keys and locks
 * were chosen in the same order as the English alphabet.
 *
 * Return the lowest number of moves to acquire all keys. If it is impossible, return -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 30
 * ! grid[i][j] is either an English letter, '.', '#', or '@'.
 * ! The number of keys in the grid is in the range [1, 6].
 * ! Each key in the grid is unique.
 * ! Each key in the grid has a matching lock.
 */

class Solution {
public:
    // BFS: time O(MN(2^K)), space O(MN(2^K))
    int shortestPathAllKeys(std::vector<std::string>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        // there are at most 6 keys,
        // so we can encode them into an integer
        int targetKeychain = 0;
        std::queue<std::tuple<int, int, int>> queue; // <x, y, keychain>
        std::vector<std::vector<std::unordered_set<int>>> visited(m, std::vector<std::unordered_set<int>>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '@') {
                    queue.emplace(i, j, 0);
                    visited[i][j].insert(0);
                } else if (isKey(grid[i][j])) {
                    targetKeychain = addKey(targetKeychain, grid[i][j]);
                }
            }
        }
        static const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
        int moves = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y, keychain] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    // case 1: out of boundary
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;
                    // case 2: hit wall
                    if (grid[i][j] == '#')
                        continue;
                    // case 3: find a lock but we can't open it
                    if (isLock(grid[i][j]) && !canOpen(keychain, grid[i][j]))
                        continue;
                    // case 4: find a key, add it to keychain
                    int newKeychain = keychain;
                    if (isKey(grid[i][j])) {
                        newKeychain = addKey(keychain, grid[i][j]);
                    }
                    // case 5: check the keychain is visited
                    if (visited[i][j].count(newKeychain))
                        continue;
                    // case 6: check the keychain is target
                    if (newKeychain == targetKeychain)
                        return moves + 1;

                    queue.emplace(i, j, newKeychain);
                    visited[i][j].insert(newKeychain);
                }
            }
            moves++;
        }
        return -1;
    }

private:
    int addKey(int currentKeychain, char key)
    {
        // keys are lowercase letters
        return currentKeychain | (1 << (key - 'a'));
    }

    bool canOpen(int currentKeychain, char lock)
    {
        // locks are uppercase letters
        return (currentKeychain >> (lock - 'A')) & 1;
    }

    bool isLock(char c)
    {
        return c >= 'A' && c <= 'Z';
    }

    bool isKey(char c)
    {
        return c >= 'a' && c <= 'z';
    }
};
