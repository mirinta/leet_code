#include <vector>

class Difference2D {
public:
    Difference2D(int rows, int cols) : m(rows), n(cols), diff(m + 1, std::vector<int>(n + 1, 0)), total(diff) {}

    /**
     * @brief Add delta to all the elements in the submatrix mat[x1:x2][y1:y2].
     *
     * @note x1, y1, x2 and y2 are 0-indexed.
     */
    void add(int x1, int y1, int x2, int y2, int delta)
    {
        diff[x2 + 1][y2 + 1] += delta;
        diff[x2 + 1][y1] -= delta;
        diff[x1][y2 + 1] -= delta;
        diff[x1][y1] += delta;
        changed = delta != 0;
    }

    /**
     * @brief Return the cumulative change for the element mat[x][y].
     *
     * @note x and y are 0-indexed.
     */
    int query(int x, int y)
    {
        if (!changed)
            return total[x][y];

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                total[i][j] = diff[i][j];
                if (i > 0) {
                    total[i][j] += total[i - 1][j];
                }
                if (j > 0) {
                    total[i][j] += total[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    total[i][j] -= total[i - 1][j - 1];
                }
            }
        }
        return total[x][y];
    }

private:
    const int m;
    const int n;
    bool changed{false};
    // diff[i][j] = x means add x to all the elements in the submatrix mat[0:i-1][0:j-1]
    std::vector<std::vector<int>> diff;
    std::vector<std::vector<int>> total;
};
