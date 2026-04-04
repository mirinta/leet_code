#include <string>
#include <vector>

/**
 * A string originalText is encoded using a slanted transposition cipher to a string encodedText with the help of a
 * matrix having a fixed number of rows rows.
 *
 * originalText is placed first in a top-left to bottom-right manner.
 *
 * The blue cells are filled first, followed by the red cells, then the yellow cells, and so on, until we reach the end
 * of originalText. The arrow indicates the order in which the cells are filled. All empty cells are filled with ' '.
 * The number of columns is chosen such that the rightmost column will not be empty after filling in originalText.
 *
 * encodedText is then formed by appending all characters of the matrix in a row-wise fashion.
 *
 * The characters in the blue cells are appended first to encodedText, then the red cells, and so on, and finally the
 * yellow cells. The arrow indicates the order in which the cells are accessed.
 *
 * The blue arrows depict how originalText is placed in the matrix, and the red arrows denote the order in which
 * encodedText is formed. In the above example, encodedText = "ch ie pr".
 *
 * Given the encoded string encodedText and number of rows rows, return the original string originalText.
 *
 * Note: originalText does not have any trailing spaces ' '. The test cases are generated such that there is only one
 * possible originalText.
 *
 * ! 0 <= encodedText.length <= 10^6
 * ! encodedText consists of lowercase English letters and ' ' only.
 * ! encodedText is a valid encoding of some originalText that does not have trailing spaces.
 * ! 1 <= rows <= 1000
 * ! The testcases are generated such that there is only one possible originalText.
 */

class Solution {
public:
    std::string decodeCiphertext(std::string& encodedText, int rows)
    {
        const int n = encodedText.size();
        const int cols = n / rows;
        std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));
        for (int i = 0; i < n; ++i) {
            grid[i / cols][i % cols] = encodedText[i];
        }
        std::string result;
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows && i + j < cols; ++i) {
                result.push_back(grid[i][i + j]);
            }
        }
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        return result;
    }
};
