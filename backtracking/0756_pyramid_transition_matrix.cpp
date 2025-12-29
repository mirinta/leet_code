#include <array>
#include <string>
#include <vector>

/**
 * You are stacking blocks to form a pyramid. Each block has a color, which is represented by a single letter. Each row
 * of blocks contains one less block than the row beneath it and is centered on top.
 *
 * To make the pyramid aesthetically pleasing, there are only specific triangular patterns that are allowed. A
 * triangular pattern consists of a single block stacked on top of two blocks. The patterns are given as a list of
 * three-letter strings allowed, where the first two characters of a pattern represent the left and right bottom blocks
 * respectively, and the third character is the top block.
 *
 * - For example, "ABC" represents a triangular pattern with a 'C' block stacked on top of an 'A' (left) and 'B' (right)
 * block. Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom. You
 * start with a bottom row of blocks bottom, given as a single string, that you must use as the base of the pyramid.
 *
 * Given bottom and allowed, return true if you can build the pyramid all the way to the top such that every triangular
 * pattern in the pyramid is in allowed, or false otherwise.
 *
 * ! 2 <= bottom.length <= 6
 * ! 0 <= allowed.length <= 216
 * ! allowed[i].length == 3
 * ! The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
 * ! All the values of allowed are unique.
 */

class Solution {
public:
    bool pyramidTransition(std::string bottom, std::vector<std::string>& allowed)
    {
        const int n = bottom.size();
        std::vector<std::string> pyramid(n, std::string(n, '*'));
        pyramid.back() = bottom;
        std::array<std::array<std::string, 26>, 26> grid{};
        for (const auto& s : allowed) {
            grid[s[0] - 'A'][s[1] - 'A'].push_back(s[2]);
        }
        return backtrack(pyramid, n - 2, 0, grid);
    }

private:
    bool backtrack(std::vector<std::string>& pyramid,
                   int row,
                   int col,
                   const std::array<std::array<std::string, 26>, 26>& grid)
    {
        if (row < 0)
            return true;

        for (const auto& c : grid[pyramid[row + 1][col] - 'A'][pyramid[row + 1][col + 1] - 'A']) {
            pyramid[row][col] = c;
            if (backtrack(pyramid, col + 1 > row ? row - 1 : row, col + 1 > row ? 0 : col + 1, grid))
                return true;

            pyramid[row][col] = '*';
        }
        return false;
    }
};