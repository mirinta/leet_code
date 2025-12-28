#include <vector>

/**
 * We stack glasses in a pyramid, where the first row has 1 glass, the second row has 2 glasses, and
 * so on until the 100th row.  Each glass holds one cup of champagne.
 *
 * Then, some champagne is poured into the first glass at the top.  When the topmost glass is full,
 * any excess liquid poured will fall equally to the glass immediately to the left and right of it.
 * When those glasses become full, any excess champagne will fall equally to the left and right of
 * those glasses, and so on.  (A glass at the bottom row has its excess champagne fall on the
 * floor.)
 *
 * For example, after one cup of champagne is poured, the top most glass is full.  After two cups of
 * champagne are poured, the two glasses on the second row are half full.  After three cups of
 * champagne are poured, those two cups become full - there are 3 full glasses total now.  After
 * four cups of champagne are poured, the third row has the middle glass half full, and the two
 * outside glasses are a quarter full, as pictured below.
 *
 * Now after pouring some non-negative integer cups of champagne, return how full the jth glass in
 * the ith row is (both i and j are 0-indexed.)
 *
 * ! 0 <= poured <= 10^9
 * ! 0 <= query_glass <= query_row < 100
 */

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass)
    {
        /**
         * row0:       0
         *            / \
         * row1:     0   1
         *          / \ / \
         * row2:   0   1   2
         *        / \ / \ / \
         * row3: 0   1   2   3
         *
         *       ... ... ...
         *
         * rowi-1: ... j-1 j ...
         *              \ /
         * rowi:     ... j ...
         *              / \
         * rowi+1: ... j   j+1 ...
         */
        return approach2(poured, query_row, query_glass);
    }

private:
    // DP with space optimization, time O(ROW^2), space O(ROW)
    double approach2(int poured, int query_row, int query_glass)
    {
        std::vector<double> pyramid(query_row + 1, 0);
        pyramid[0] = poured;
        for (int i = 1; i <= query_row; ++i) {
            std::vector<double> current(query_row + 1, 0);
            for (int j = 0; j <= i; ++j) {
                const double src1 = j == i ? 0 : pyramid[j];
                current[j] += std::max(0.0, src1 - 1) * 0.5;
                const double src2 = j == 0 ? 0 : pyramid[j - 1];
                current[j] += std::max(0.0, src2 - 1) * 0.5;
            }
            pyramid = current;
        }
        return std::min(1.0, pyramid[query_glass]);
    }

    // DP, time O(ROW^2), space O(ROW^2)
    double approach1(int poured, int query_row, int query_glass)
    {
        // the ith row (0-indexed) contains i+1 glasses
        std::vector<std::vector<double>> pyramid(query_row + 1, std::vector<double>(query_row + 1, 0));
        pyramid[0][0] = poured;
        for (int i = 1; i <= query_row; ++i) {
            for (int j = 0; j <= i; ++j) {
                const double src1 = j == i ? 0 : pyramid[i - 1][j];
                pyramid[i][j] += std::max(0.0, src1 - 1) * 0.5;
                const double src2 = j == 0 ? 0 : pyramid[i - 1][j - 1];
                pyramid[i][j] += std::max(0.0, src2 - 1) * 0.5;
            }
        }
        return std::min(1.0, pyramid[query_row][query_glass]);
    }
};