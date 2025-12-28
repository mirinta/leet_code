#include <string>
#include <vector>

/**
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 * (you may want to display this pattern in a fixed font for better legibility).
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 * And then read line by line: "PAHNAPLSIIGYIR".
 *
 * Write the code that will take a string and make this conversion given a number of rows.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of English letters (lower-case and upper-case), ',' and '.'.
 * ! 1 <= numRows <= 1000
 */

class Solution {
public:
    std::string convert(std::string s, int numRows)
    {
        // s = PAYPALISHIRING, numRows = 4
        // row0: P     I    N
        // row1: A   L S  I G
        // row2: Y A   H R
        // row3: P     I
        // go-down: P->A->Y->P
        // go-up: A->L->I
        // go-down: S->H->I
        // go-up: R->I->N
        // go-down: G
        if (numRows == 1)
            return s;

        // the following algorithm can't handle the case when numRows == 1
        std::vector<std::string> rows(numRows);
        for (int i = 0, rowIndex = 0, direction = -1; i < s.size(); ++i) {
            rows[rowIndex].push_back(s[i]);
            if (rowIndex == 0 || rowIndex == numRows - 1) {
                direction *= -1;
            }
            rowIndex += direction;
        }
        std::string result;
        for (const auto& row : rows) {
            result.append(row);
        }
        return result;
    }
};
