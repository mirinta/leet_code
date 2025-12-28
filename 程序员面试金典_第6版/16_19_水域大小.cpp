#include <algorithm>
#include <vector>

/**
 * 你有一个用于表示一片土地的整数矩阵land，该矩阵中每个点的值代表对应地点的海拔高度。
 *
 * 若值为0则表示水域。由垂直、水平或对角连接的水域为池塘。
 *
 * 池塘的大小是指相连接的水域的个数。
 *
 * 编写一个方法来计算矩阵中所有池塘的大小，返回值需要从小到大排序。
 *
 * ! 0 < len(land) <= 1000
 * ! 0 < len(land[i]) <= 1000
 */

class Solution {
public:
    std::vector<int> pondSizes(std::vector<std::vector<int>>& land)
    {
        const int m = land.size();
        const int n = land[0].size();
        std::vector<int> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (land[i][j] == 0) {
                    result.push_back(dfs(land, i, j));
                }
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

private:
    int dfs(std::vector<std::vector<int>>& land, int i, int j)
    {
        if (i < 0 || i >= land.size() || j < 0 || j >= land[0].size())
            return 0;

        if (land[i][j] != 0)
            return 0;

        land[i][j] = -1;
        int result = 1;
        result += dfs(land, i - 1, j);
        result += dfs(land, i + 1, j);
        result += dfs(land, i, j - 1);
        result += dfs(land, i, j + 1);
        result += dfs(land, i - 1, j - 1);
        result += dfs(land, i - 1, j + 1);
        result += dfs(land, i + 1, j - 1);
        result += dfs(land, i + 1, j + 1);
        return result;
    }
};