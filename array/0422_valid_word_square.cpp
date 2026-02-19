#include <string>
#include <vector>

/**
 * Given an array of strings words, return true if it forms a valid word square.
 *
 * A sequence of strings forms a valid word square if the kth row and column read the same string,
 * where 0 <= k < max(numRows, numColumns).
 *
 * ! 1 <= words.length <= 500
 * ! 1 <= words[i].length <= 500
 * ! words[i] consists of only lowercase English letters.
 */

class Solution {
public:
    bool validWordSquare(std::vector<std::string>& words)
    {
        const int m = words.size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < words[i].size(); ++j) {
                if (j >= m || i >= words[j].size())
                    return false;

                if (words[i][j] != words[j][i])
                    return false;
            }
        }
        return true;
    }
};
