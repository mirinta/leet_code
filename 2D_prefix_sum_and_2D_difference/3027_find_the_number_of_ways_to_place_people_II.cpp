#include <set>
#include <unordered_map>
#include <vector>

/**
 * You are given a 2D array points of size n x 2 representing integer coordinates of some points on
 * a 2D-plane, where points[i] = [xi, yi].
 *
 * We define the right direction as positive x-axis (increasing x-coordinate) and the left direction
 * as negative x-axis (decreasing x-coordinate). Similarly, we define the up direction as positive
 * y-axis (increasing y-coordinate) and the down direction as negative y-axis (decreasing
 * y-coordinate)
 *
 * You have to place n people, including Chisato and Takina, at these points such that there is
 * exactly one person at every point. Chisato wants to be alone with Takina, so Chisato will build a
 * rectangular fence with Chisato's position as the upper left corner and Takina's position as the
 * lower right corner of the fence (Note that the fence might not enclose any area, i.e. it can be a
 * line). If any person other than Chisato and Takina is either inside the fence or on the fence,
 * Chisato will be sad.
 *
 * Return the number of pairs of points where you can place Chisato and Takina, such that Chisato
 * does not become sad on building the fence.
 *
 * Note that Chisato can only build a fence with Chisato's position as the upper left corner, and
 * Takina's position as the lower right corner. For example, Chisato cannot build either of the
 * fences in the picture below with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:
 *
 * - With Chisato at (3, 3) and Takina at (1, 1), Chisato's position is not the upper left corner
 * and Takina's position is not the lower right corner of the fence.
 *
 * - With Chisato at (1, 3) and Takina at (1, 1), Takina's position is not the lower right corner of
 * the fence.
 *
 * ! 2 <= n <= 1000
 * ! points[i].length == 2
 * ! -10^9 <= points[i][0], points[i][1] <= 10^9
 * ! All points[i] are distinct.
 */

class PrefixSum2D {
public:
    explicit PrefixSum2D(const std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        presum.resize(m + 1);
        std::fill(presum.begin(), presum.end(), std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = mat[i - 1][j - 1] + presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

private:
    std::vector<std::vector<int>> presum;
};

class Solution {
public:
    int numberOfPairs(std::vector<std::vector<int>>& points)
    {
        std::set<int> xCoords;
        std::set<int> yCoords;
        for (const auto& p : points) {
            xCoords.insert(p[0]);
            yCoords.insert(p[1]);
        }
        std::unordered_map<int, int> mapX;
        std::unordered_map<int, int> mapY;
        for (auto iter = xCoords.begin(); iter != xCoords.end(); ++iter) {
            mapX[*iter] = std::distance(xCoords.begin(), iter);
        }
        for (auto iter = yCoords.begin(); iter != yCoords.end(); ++iter) {
            mapY[*iter] = std::distance(yCoords.begin(), iter);
        }
        const int m = mapX.size();
        const int n = mapY.size();
        std::vector<std::vector<int>> mat(m, std::vector<int>(n, 0));
        for (const auto& p : points) {
            mat[mapX[p[0]]][mapY[p[1]]] = 1;
        }
        PrefixSum2D presum(mat);
        int result = 0;
        for (int i = 0; i < points.size(); ++i) {
            const int x1 = points[i][0];
            const int y1 = points[i][1];
            for (int j = i + 1; j < points.size(); ++j) {
                const int x2 = points[j][0];
                const int y2 = points[j][1];
                //      y                        o--->y
                //      ^                        |
                //      |                        v
                //      o--->x                   x
                // original coord frame A     matrix coord frame B
                // top-left in A = top-right in B
                // bottom-right in A = bottom-left in B
                // we need top-left and bottom-right in B when calling query()
                const bool case1 = x1 <= x2 && y1 >= y2 &&
                                   presum.query(mapX[x1], mapY[y2], mapX[x2], mapY[y1]) == 2; // (x1,y1) is top-left
                const bool case2 = x2 <= x1 && y2 >= y1 &&
                                   presum.query(mapX[x2], mapY[y1], mapX[x1], mapY[y2]) == 2; // (x2,y2) is top-left
                if (case1 || case2) {
                    result++;
                }
            }
        }
        return result;
    }
};