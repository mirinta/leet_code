#include <bitset>
#include <vector>

/**
 * Android devices have a special lock screen with a 3 x 3 grid of dots. Users can set an "unlock
 * pattern" by connecting the dots in a specific sequence, forming a series of joined line segments
 * where each segment's endpoints are two consecutive dots in the sequence. A sequence of k dots is
 * a valid unlock pattern if both of the following are true:
 *
 * - All the dots in the sequence are distinct.
 *
 * - If the line segment connecting two consecutive dots in the sequence passes through the center
 *   of any other dot, the other dot must have previously appeared in the sequence. No jumps through
 *   the center non-selected dots are allowed.
 *
 *   - For example, connecting dots 2 and 9 without dots 5 or 6 appearing beforehand is valid
 *     because the line from dot 2 to dot 9 does not pass through the center of either dot 5 or 6.
 *
 *   - However, connecting dots 1 and 3 without dot 2 appearing beforehand is invalid because the
 *     line from dot 1 to dot 3 passes through the center of dot 2.
 *
 * ! 1 <= m, n <= 9
 */

class Solution {
public:
    int numberOfPatterns(int m, int n)
    {
        std::memset(check, -1, sizeof(check));
        check[1][3] = 2;
        check[1][7] = 4;
        check[1][9] = 5;
        check[2][8] = 5;
        check[3][1] = 2;
        check[3][7] = 5;
        check[3][9] = 6;
        check[4][6] = 5;
        check[6][4] = 5;
        check[7][1] = 4;
        check[7][3] = 5;
        check[7][9] = 8;
        check[8][2] = 5;
        check[9][1] = 5;
        check[9][3] = 6;
        check[9][7] = 8;
        std::bitset<10> visited;
        int result = 0;
        for (int i = 1; i <= 9; ++i) {
            backtrack(result, visited, i, 1, m, n);
        }
        return result;
    }

private:
    int check[10][10];

    void backtrack(int& result, std::bitset<10>& visited, int curr, int keys, int m, int n)
    {
        if (keys >= m && keys <= n) {
            result++;
        } else if (keys > n)
            return;

        visited[curr] = true;
        for (int next = 1; next <= 9; ++next) {
            if (visited[next])
                continue;

            if (check[curr][next] != -1 && !visited[check[curr][next]])
                continue;

            backtrack(result, visited, next, keys + 1, m, n);
        }
        visited[curr] = false;
    }
};