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
        if (words.empty())
            return false;

        // check whether it is a square matrix
        const size_t m = words.size();
        size_t n = 0;
        for (const auto& word : words) {
            n = std::max(n, word.size());
        }
        if (m != n)
            return false;

        // check whether it is a symmetric matrix
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < n; ++j) {
                const auto& c1 = j < words[i].size() ? words[i][j] : '#';
                const auto& c2 = i < words[j].size() ? words[j][i] : '#';
                if (c1 != c2)
                    return false;
            }
        }
        return true;
    }
};
