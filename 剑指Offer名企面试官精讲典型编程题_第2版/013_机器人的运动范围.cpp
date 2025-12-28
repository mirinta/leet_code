#include <vector>

/**
 * 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
 *
 * 一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
 * 也不能进入行坐标和列坐标的数位之和大于k的格子。
 *
 * 例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。
 * 但它不能进入方格 [35, 38]，因为3+5+3+8=19。
 *
 * 请问该机器人能够到达多少个格子？
 *
 * ! 1 <= n,m <= 100
 * ! 0 <= k <= 20
 */

class Solution {
public:
    int movingCount(int m, int n, int k)
    {
        if (m < 1 || n < 1 || k < 0)
            return 0;

        int count = 0;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        dfs(count, visited, 0, 0, m, n, k);
        return count;
    }

private:
    void dfs(int& count, std::vector<std::vector<bool>>& visited, int x, int y, int m, int n, int k)
    {
        if (x < 0 || x >= m || y < 0 || y >= n)
            return;

        if (visited[x][y] || digitSum(x) + digitSum(y) > k)
            return;

        count++;
        visited[x][y] = true;
        dfs(count, visited, x + 1, y, m, n, k);
        dfs(count, visited, x - 1, y, m, n, k);
        dfs(count, visited, x, y + 1, m, n, k);
        dfs(count, visited, x, y - 1, m, n, k);
    }

    int digitSum(int num)
    {
        int sum = 0;
        while (num) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
};