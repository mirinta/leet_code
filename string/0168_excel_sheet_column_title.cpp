#include <string>

/**
 * Given an integer columnNumber, return its corresponding column title as it appears in an Excel
 * sheet.
 *
 * ! 1 <= columnNumber <= 2^31 - 1
 */

class Solution {
public:
    std::string convertToTitle(int columnNumber)
    {
        std::string result;
        while (columnNumber) {
            columnNumber--;
            result.push_back(columnNumber % 26 + 'A');
            columnNumber /= 26;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};